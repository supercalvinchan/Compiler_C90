int f(){
  int a = 10;
  int b = 2;

  a = ((a + b) << 9)*20;
  a = ((a + b) >> 3)/7;
  a = (((a + b) >> 3)/7) - 201;
  a =  (a % 4) | 23;
  return a;
}
