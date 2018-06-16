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

int f(){
    int a;
    a = 200;
    return d(123+21,5) + g(20);
}
