/* { dg-do compile } */ 
/* { dg-options "-O2 -ftree-loop-linear -fdump-tree-ltrans-all" } */
/* { dg-require-effective-target size32plus } */



int medium_loop_interchange(int A[100][200])
{
  int i,j;

  /* This loop should be interchanged. */

  for(j = 0; j < 200; j++)
    for(i = 0; i < 100; i++)
      A[i][j] = A[i][j] + A[i][j];

  return A[1][1];
}

/* { dg-final { scan-tree-dump-times "transformed loop" 1 "ltrans"} } */ 
/* { dg-final { cleanup-tree-dump "ltrans" } } */
