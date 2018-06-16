#include <stdio.h>
#include <cstdlib>
int f();

int main()
{
fprintf(stderr, "my result = %d\n", f());
return !( "0.012" == f() );
}
