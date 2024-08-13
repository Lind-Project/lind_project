/* { dg-do compile } */
/* { dg-options "-O -fdump-tree-fre-details -fdump-tree-optimized" } */
#if (__SIZEOF_INT__ == __SIZEOF_FLOAT__)
typedef int intflt;
#elif (__SIZEOF_LONG__ == __SIZEOF_FLOAT__)
typedef long intflt;
#else
#error Add target support here for type that will union float size
#endif

struct X {
  int i;
  union {
    intflt j;
    intflt k;
    float f;
  } u;
};

intflt foo(intflt j)
{
  struct X a;

  a.u.j = j;
  a.u.f = a.u.f;
  a.u.f = a.u.f;
  a.u.j = a.u.j;
  a.u.f = a.u.f;
  return a.u.k;
}

/* { dg-final { scan-tree-dump-times "Inserted pretmp" 1 "fre" } } */
/* { dg-final { scan-tree-dump-times "Replaced a.u.f with pretmp" 3 "fre" } } */
/* { dg-final { scan-tree-dump-times "Replaced a.u.k with j" 1 "fre" } } */
/* { dg-final { scan-tree-dump "= VIEW_CONVERT_EXPR<float>\\\(j_" "fre" } } */
/* { dg-final { scan-tree-dump "return j" "optimized" } } */
/* { dg-final { cleanup-tree-dump "fre" } } */
/* { dg-final { cleanup-tree-dump "optimized" } } */
