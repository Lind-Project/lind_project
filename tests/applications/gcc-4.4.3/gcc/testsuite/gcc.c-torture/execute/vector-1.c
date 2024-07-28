/* Check that vector extraction works correctly. */

#define vector __attribute__((vector_size(16) ))

int f0(vector int t)
{
  return ((int*)&t)[0];
}
int f1(vector int t)
{
  return ((int*)&t)[1];
}
int f2(vector int t)
{
  return ((int*)&t)[2];
}
int f3(vector int t)
{
  return ((int*)&t)[3];
}
int main(void)
{
  vector int a = {0, 1, 2, 3};
  /* Make sure that we have the correct size for the vectors. */
  if (sizeof(int) != 4)
    __builtin_exit (0);
  if (f0(a) != 0)
    __builtin_abort ();
  if (f1(a) != 1)
    __builtin_abort ();
  if (f2(a) != 2)
    __builtin_abort ();
  if (f3(a) != 3)
    __builtin_abort ();
  return 0;
}
