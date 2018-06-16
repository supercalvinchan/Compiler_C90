int f(){
  int a = 100;
  int b = 12;
  a = ((a + b) << 2)*2;
  b = ((a + b) >> 10)/7;
  return a||b;
}
