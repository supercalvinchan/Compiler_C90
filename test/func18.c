int d(int p,int k){
  if (p<=1){
    return 1;
  } else {
    return d(p-1,k);
  }
}

int g(int p){
  if (p<=1){
    return 1;
  } else {
    return d(p-1,p);
  }
}

int m(){
  return 7;
}

int f(){
    int a;
    a = 200;
    return d(123+21,a) + g(a) + m();
}
