/* { dg-do compile } */
/* { dg-options "-O3 -fipa-cp -fipa-cp-clone -fdump-ipa-cp -fno-early-inlining"  } */
/* { dg-skip-if "PR 25442" { "*-*-*" } { "-fpic" "-fPIC" } { "" } } */

#include <stdio.h>
void send_addr (int *);
int g (int b, int c)
{
  printf ("%d %d\n", b, c);
}
int f (int a)
{
  if (a > 0)
    g (a, 3);
  else
    g (a, 5); 	
   
  send_addr (&a);
}
int main ()
{
  f (7);
  return 0;	
}


/* { dg-final { scan-ipa-dump-times "versioned function" 1 "cp"  } } */
/* { dg-final { scan-ipa-dump-times "replacing param a with const 7" 1 "cp"  } } */
/* { dg-final { cleanup-ipa-dump "cp" } } */


