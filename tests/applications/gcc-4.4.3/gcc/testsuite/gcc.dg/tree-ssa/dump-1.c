/* { dg-do compile } */
/* { dg-options "-O1 -fdump-tree-profile-details" } */

int f(void)
{
  return 0;
}

/* { dg-final { cleanup-tree-dump "profile" } } */
