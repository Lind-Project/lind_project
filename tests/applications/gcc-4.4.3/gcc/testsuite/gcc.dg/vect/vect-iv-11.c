/* { dg-require-effective-target vect_int } */

#include <stdio.h>
#include <stdarg.h>
#include "tree-vect.h"

int main1 (int len)
{  
  int s = 0;
  int i = len;

  /* vectorization of induction with reduction.  */
  for ( ; i > 1; i -=2)
    s += i;

  return s;
}

int main (void)
{ 
  int s;
  check_vect ();
  
  s = main1 (26);
  if (s != 182)
    abort ();

  return 0;
} 

/* { dg-final { scan-tree-dump-times "vectorized 1 loops" 1 "vect" } } */
/* { dg-final { cleanup-tree-dump "vect" } } */
