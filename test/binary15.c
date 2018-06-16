int f(){
  int a = 10;
  int b = 12;
  a |= (3 + b);
  a &= (4+ a);

  return a;
}
