/* { dg-do "compile" } */
/* { dg-options "-O2 -fdump-tree-fre" } */

struct S { unsigned f; };

int
foo ( struct S *p)
{
  int *q = (int *)&p->f;
  int i = *q;
  return i + p->f;
}


/*  There should only be one load of p->f because fwprop can change *(int *)&p->f into just (int)p->f.  */
/* { dg-final { scan-tree-dump-times "p_.\\\(D\\\)->f" 1 "fre" } } */
/* { dg-final { cleanup-tree-dump "fre" } } */

