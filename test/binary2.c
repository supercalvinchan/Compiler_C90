int f(){
  int a = 10;
  int b = 2;
  a = (a + b) << 9;
  b = (a + b) >> 3;
  return b;
}
