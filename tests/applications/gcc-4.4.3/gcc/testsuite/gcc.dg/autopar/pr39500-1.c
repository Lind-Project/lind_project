/* pr39500: autopar fails to parallel */
/* origin: nemokingdom@gmail.com(LiFeng) */
/* { dg-do compile } */
/* { dg-options "-O2 -ftree-parallelize-loops=4 -fdump-tree-parloops-details" } */

void abort (void);

int main (void)
{
  int i;
  int x[1000];

  for (i = 0; i < 100; i++)
    x[i] = x[i+100];

  for (i = 0; i < 100; i++)
    {
      if (x[i] != x[i+100])
       abort ();
    }

  return 0;
}

/* Check that the first loop in parloop got parallelized.  */

/* { dg-final { scan-tree-dump-times "SUCCESS: may be parallelized" 1 "parloops" } } */
/* { dg-final { cleanup-tree-dump "parloops" } } */
