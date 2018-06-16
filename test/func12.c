int g(int parameter){
  if (parameter == 2){
    return 20;
  } else {
    return 0;
  }
}
int f(){
  int d = 0;
  int p = 0;
  for (d = 0; d<120; d++){
    p+= g(d);
  }
  return p;
}
