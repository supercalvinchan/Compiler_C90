int i = 4;
int d = 6;

int g(){
  return i + d;
}

int f()
{
  i = 8;
  return g();
}
