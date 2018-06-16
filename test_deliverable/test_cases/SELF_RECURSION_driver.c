#include <stdio.h>
int f(9);

int main()
{
fprintf(stderr, "my result = %d\n", f());
return !( 45 == f(9) );
}
