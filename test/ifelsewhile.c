int f()
{
int a = 4;
int b = 8;
if(a < b)
{
  a = 10;
  while(a > b)
  {
    b = b + 1;
  }
}
return b;

}
