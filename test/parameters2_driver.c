#include <stdio.h>
int f(int a, int b);

int main()
{
  fprintf(stderr, "my result = %d\n", f(2,3));
  return !(5 == f(2,3));
}
