int g(int* d)
{
int** a;
int* b;
int c = 5;
b = &c;
a = &b;
*d = 100;
return **a + *d;

}

int f()
{
  int k = 9;
  return g(&k);
}
