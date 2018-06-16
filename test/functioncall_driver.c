#include <stdio.h>
int f();
int g();
int main()
{
  fprintf(stderr, "my result = %d\n", g());
  return !(15 == g());
}
