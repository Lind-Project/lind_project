/*
 * Copyright (c) 2011 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


// Make sure that winmm.lib is added to the linker's input.
#pragma comment(lib, "winmm.lib")
#include "native_client/src/include/portability.h"
#include <mmsystem.h>
#include <windows.h>

#include "native_client/src/include/checked_cast.h"
#include "native_client/src/shared/platform/win/time.h"
#include "native_client/src/shared/platform/win/lock.h"

namespace {

// From MSDN, FILETIME "Contains a 64-bit value representing the number of
// 100-nanosecond intervals since January 1, 1601 (UTC)."
int64_t FileTimeToMicroseconds(const FILETIME& ft) {
  // Need to nacl_bit_cast to fix alignment, then divide by 10 to convert
  // 100-nanoseconds to milliseconds. This only works on little-endian
  // machines.
  return nacl_bit_cast<int64_t, FILETIME>(ft) / 10;
}

void MicrosecondsToFileTime(int64_t us, FILETIME* ft) {
/*  DCHECK(us >= 0) << "Time is less than 0, negative values are not "
 *      "representable in FILETIME";
 */

  // Multiply by 10 to convert milliseconds to 100-nanoseconds. Nacl_bit_cast
  // will handle alignment problems. This only works on little-endian machines.
  *ft = nacl_bit_cast<FILETIME, int64_t>(us * 10);
}

}  // namespace

// Time -----------------------------------------------------------------------

// The internal representation of Time uses FILETIME, whose epoch is 1601-01-01
// 00:00:00 UTC.  ((1970-1601)*365+89)*24*60*60*1000*1000, where 89 is the
// number of leap year days between 1601 and 1970: (1970-1601)/4 excluding
// 1700, 1800, and 1900.
// static
const int64_t NaCl::Time::kTimeTToMicrosecondsOffset =
    GG_INT64_C(11644473600000000);

// static
int64_t NaCl::Time::CurrentWallclockMicroseconds() {
  FILETIME ft;
  ::GetSystemTimeAsFileTime(&ft);
  return FileTimeToMicroseconds(ft);
}

// static
NaCl::Time NaCl::Time::FromFileTime(FILETIME ft) {
  return Time(FileTimeToMicroseconds(ft));
}

FILETIME NaCl::Time::ToFileTime() const {
  FILETIME utc_ft;
  MicrosecondsToFileTime(us_, &utc_ft);
  return utc_ft;
}

// static
NaCl::Time NaCl::Time::FromExploded(bool is_local, const Exploded& exploded) {
  // Create the system struct representing our exploded time. It will either be
  // in local time or UTC.
  SYSTEMTIME st;
  st.wYear = nacl::assert_cast<WORD>(exploded.year);
  st.wMonth = nacl::assert_cast<WORD>(exploded.month);
  st.wDayOfWeek = nacl::assert_cast<WORD>(exploded.day_of_week);
  st.wDay = nacl::assert_cast<WORD>(exploded.day_of_month);
  st.wHour = nacl::assert_cast<WORD>(exploded.hour);
  st.wMinute = nacl::assert_cast<WORD>(exploded.minute);
  st.wSecond = nacl::assert_cast<WORD>(exploded.second);
  st.wMilliseconds = nacl::assert_cast<WORD>(exploded.millisecond);

  // Convert to FILETIME.
  FILETIME ft;
  if (!SystemTimeToFileTime(&st, &ft)) {
    // NOTREACHED() << "Unable to convert time";
    return Time(0);
  }

  // Ensure that it's in UTC.
  if (is_local) {
    FILETIME utc_ft;
    LocalFileTimeToFileTime(&ft, &utc_ft);
    return Time(FileTimeToMicroseconds(utc_ft));
  }
  return Time(FileTimeToMicroseconds(ft));
}

void NaCl::Time::Explode(bool is_local, Exploded* exploded) const {
  // FILETIME in UTC.
  FILETIME utc_ft;
  MicrosecondsToFileTime(us_, &utc_ft);

  // FILETIME in local time if necessary.
  BOOL success = TRUE;
  FILETIME ft;
  if (is_local)
    success = FileTimeToLocalFileTime(&utc_ft, &ft);
  else
    ft = utc_ft;

  // FILETIME in SYSTEMTIME (exploded).
  SYSTEMTIME st;
  if (!success || !FileTimeToSystemTime(&ft, &st)) {
    // NOTREACHED() << "Unable to convert time, don't know why";
    ZeroMemory(exploded, sizeof(*exploded));
    return;
  }

  exploded->year = st.wYear;
  exploded->month = st.wMonth;
  exploded->day_of_week = st.wDayOfWeek;
  exploded->day_of_month = st.wDay;
  exploded->hour = st.wHour;
  exploded->minute = st.wMinute;
  exploded->second = st.wSecond;
  exploded->millisecond = st.wMilliseconds;
}

// TimeTicks ------------------------------------------------------------------
NaCl::TimeTicks::TickFunction NaCl::TimeTicks::tick_function_=
    reinterpret_cast<TickFunction>(&timeGetTime);

// static
NaCl::TimeTicks NaCl::TimeTicks::Now() {
  // Uses the multimedia timers on Windows to get a higher resolution clock.
  // timeGetTime() provides a resolution which is variable depending on
  // hardware and system configuration.  It can also be changed by other
  // apps.  This class does not attempt to change the resolution of the
  // timer, because we don't want to affect other applications.

  // timeGetTime() should at least be accurate to ~5ms on all systems.
  // timeGetTime() returns a 32-bit millisecond counter which has rollovers
  // every ~49 days.
  static DWORD last_tick_count = 0;
  static int64_t tick_rollover_accum = 0;
  static Lock* tick_lock = NULL;  // To protect during rollover periods.

  // Lazily create the lock we use.
  if (!tick_lock) {
    Lock* new_lock = new Lock;
    if (InterlockedCompareExchangePointer(
        reinterpret_cast<PVOID*>(&tick_lock), new_lock, NULL)) {
      delete new_lock;
    }
  }

  // Atomically protect the low and high 32bit values for time.
  // In the future we may be able to optimize with
  // InterlockedCompareExchange64, but that doesn't work on XP.
  DWORD tick_count;
  int64_t rollover_count;
  /* lint complains about this, ignore */{
    AutoLock lock(*tick_lock);
    tick_count = tick_function_();
    if (tick_count < last_tick_count)
      tick_rollover_accum += GG_INT64_C(0x100000000);

    last_tick_count = tick_count;
    rollover_count = tick_rollover_accum;
  }

  // GetTickCount returns milliseconds, we want microseconds.
  return TimeTicks((tick_count + rollover_count) *
                   Time::kMicrosecondsPerMillisecond);
}

// Overview of time counters:
// (1) CPU cycle counter. (Retrieved via RDTSC)
// The CPU counter provides the highest resolution time stamp and is the least
// expensive to retrieve. However, the CPU counter is unreliable and should not
// be used in production. Its biggest issue is that it is per processor and it
// is not synchronized between processors. Also, on some computers, the counters
// will change frequency due to thermal and power changes, and stop in some
// states.
//
// (2) QueryPerformanceCounter (QPC). The QPC counter provides a high-
// resolution (100 nanoseconds) time stamp but is comparatively more expensive
// to retrieve. What QueryPerformanceCounter actually does is up to the HAL.
// (with some help from ACPI).
// According to http://blogs.msdn.com/oldnewthing/archive/2005/09/02/459952.aspx
// in the worst case, it gets the counter from the rollover interrupt on the
// programmable interrupt timer. In best cases, the HAL may conclude that the
// RDTSC counter runs at a constant frequency, then it uses that instead. On
// multiprocessor machines, it will try to verify the values returned from
// RDTSC on each processor are consistent with each other, and apply a handful
// of workarounds for known buggy hardware. In other words, QPC is supposed to
// give consistent result on a multiprocessor computer, but it is unreliable in
// reality due to bugs in BIOS or HAL on some, especially old computers.
// With recent updates on HAL and newer BIOS, QPC is getting more reliable but
// it should be used with caution.
//
// (3) System time. The system time provides a low-resolution (typically 10ms
// to 55 milliseconds) time stamp but is comparatively less expensive to
// retrieve and more reliable.

// static
NaCl::TimeTicks NaCl::TimeTicks::UnreliableHighResNow() {
  // Cached clock frequency -> microseconds. This assumes that the clock
  // frequency is faster than one microsecond (which is 1MHz, should be OK).
  static int64_t ticks_per_microsecond = 0;

  if (ticks_per_microsecond == 0) {
    LARGE_INTEGER ticks_per_sec = { 0, 0 };
    if (!QueryPerformanceFrequency(&ticks_per_sec))
      return TimeTicks(0);  // Broken, we don't guarantee this function works.
    ticks_per_microsecond =
        ticks_per_sec.QuadPart / Time::kMicrosecondsPerSecond;
  }

  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return TimeTicks(now.QuadPart / ticks_per_microsecond);
}
