#include <stdio.h>
int f();

int main()
{
  fprintf(stderr, "my result = %d\n", f());
return !( 512 == f() );
}
