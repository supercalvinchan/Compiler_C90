int f(){
  int* i;
  int d;
  i = &d;
  *i = 123;
  return d+d;
}
