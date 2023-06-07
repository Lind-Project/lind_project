// Author: Nicholas Renner
//
// Pipes for SafePOSIX based on Lock-Free Circular Buffer

#![allow(dead_code)]

use parking_lot::Mutex;
use std::slice;
use std::sync::Arc;
use std::sync::atomic::{AtomicBool, AtomicU32, Ordering};
use ringbuf::{RingBuffer, Producer, Consumer};
use std::cmp::min;
use std::fmt;

const O_RDONLY: i32 = 0o0;
const O_WRONLY: i32 = 0o1;
const O_RDWRFLAGS: i32 = 0o3;
const PAGE_SIZE: usize = 4096;

const CANCEL_CHECK_INTERVAL: usize = 1048576; // check to cancel pipe reads every 2^20 iterations

pub fn new_pipe(size: usize) -> EmulatedPipe {
    EmulatedPipe::new_with_capacity(size)
}

#[derive(Clone)]
pub struct EmulatedPipe {
    write_end: Arc<Mutex<Producer<u8>>>,
    read_end: Arc<Mutex<Consumer<u8>>>,
    pub refcount_write: Arc<AtomicU32>,
    pub refcount_read: Arc<AtomicU32>,
    eof: Arc<AtomicBool>,
    size: usize
}

impl EmulatedPipe {
    pub fn new_with_capacity(size: usize) -> EmulatedPipe {
        let rb = RingBuffer::<u8>::new(size);
        let (prod, cons) = rb.split();
        EmulatedPipe { write_end: Arc::new(Mutex::new(prod)), read_end: Arc::new(Mutex::new(cons)), refcount_write: Arc::new(AtomicU32::new(1)), refcount_read: Arc::new(AtomicU32::new(1)), eof: Arc::new(AtomicBool::new(false)), size: size}
    }

    pub fn set_eof(&self) {
        self.eof.store(true, Ordering::Relaxed);
    }

    pub fn get_write_ref(&self) -> u32 {
        self.refcount_write.load(Ordering::Relaxed)
    }

    pub fn get_read_ref(&self) -> u32 {
        self.refcount_read.load(Ordering::Relaxed)
    }

    pub fn incr_ref(&self, flags: i32) {
        if (flags & O_RDWRFLAGS) == O_RDONLY {self.refcount_read.fetch_add(1, Ordering::Relaxed);}
        if (flags & O_RDWRFLAGS) == O_WRONLY {self.refcount_write.fetch_add(1, Ordering::Relaxed);}
    }

    pub fn decr_ref(&self, flags: i32) {
        if (flags & O_RDWRFLAGS) == O_RDONLY {self.refcount_read.fetch_sub(1, Ordering::Relaxed);}
        if (flags & O_RDWRFLAGS) == O_WRONLY {self.refcount_write.fetch_sub(1, Ordering::Relaxed);}
    }

    // Write length bytes from pointer into pipe
    pub fn write_to_pipe(&self, ptr: *const u8, length: usize) -> i32 {

        let mut bytes_written = 0;

        let buf = unsafe {
            assert!(!ptr.is_null());
            slice::from_raw_parts(ptr, length)
        };

        let mut write_end = self.write_end.lock();

        while bytes_written < length {
            if self.get_read_ref() == 0 { return -1 } // EPIPE, all read ends are closed

            let remaining = write_end.remaining();
            // we write if the pipe is empty, otherwise we try to limit writes to 4096 bytes (unless whats leftover of this write is < 4096)
            if remaining != self.size  && (length - bytes_written) > PAGE_SIZE && remaining < PAGE_SIZE { continue };
            let bytes_to_write = min(length, bytes_written as usize + remaining);
            write_end.push_slice(&buf[bytes_written..bytes_to_write]);
            bytes_written = bytes_to_write;
        }   

        bytes_written as i32
    }

    // Read length bytes from the pipe into pointer
    // Will wait for bytes unless pipe is empty and eof is set.
    pub fn read_from_pipe(&self, ptr: *mut u8, length: usize) -> i32 {

        let buf = unsafe {
            assert!(!ptr.is_null());
            slice::from_raw_parts_mut(ptr, length)
        };

        let mut read_end = self.read_end.lock();
        let mut pipe_space : usize = read_end.len();

        // wait for something to be in the pipe, but break on eof
        // check cancel point after 2^20 cycles just in case
        while pipe_space == 0 {
            if self.eof.load(Ordering::SeqCst) { return 0; }

            pipe_space = read_end.len();
        }

        let bytes_to_read = min(length, pipe_space);
        read_end.pop_slice(&mut buf[0..bytes_to_read]);
   
        bytes_to_read as i32
    }

}

impl fmt::Debug for EmulatedPipe {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("EmulatedPipe")
         .field("refcount read", &self.refcount_read)
         .field("refcount write", &self.refcount_write)
         .field("eof", &self.eof)
         .finish()
    }
}
