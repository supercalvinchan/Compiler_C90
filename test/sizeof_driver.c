#include <stdio.h>

char f();

int main()
{
  fprintf(stderr, "my result = %d\n", f());
  return !( 5 == f() );
}
