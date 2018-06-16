int g (int d, int p){
  return d;
}

int f(){
  int a = 5;
  a = g(a,7) + g(a,9);
  return a;
}
