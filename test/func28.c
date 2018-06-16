int g(int x);
int l();


int k(int x, int y){
  if ((x==0) || (y==0))
  {
    return 1;
  }
  else
  {
    return k(x-1+x,y-1)+1 + g(x);
  }
}

int g(int x){
  return x + l();
}

int l(){
  return 7;
}


int f(){
    int i;
    i = k(2,3) + k(1,2);
    return i;
}
