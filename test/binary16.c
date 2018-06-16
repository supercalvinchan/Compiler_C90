int f(){
  int a = 10;
  int b = 12;
  a |= (3 + b);
  a &= (4+ a);
  b = a++;
  a = a--;
  b = --a;
  b = ++b;

  return b;
}
