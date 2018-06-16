#include <stdio.h>
int f(int a, int b, int c, int d, int e, int f);

int main()
{
  fprintf(stderr, "my result = %d\n", f(2,3,4,5,6,7));
return !( 27 == f(2,3,4,5,6,7) );
}
