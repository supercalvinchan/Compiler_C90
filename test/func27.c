int g(int x, int y){
  if ((x==0) || (y==0))
    return 1;
  else
    return g(x-1+x,y-1)+1;
}


int f(){
    int i;
    i = g(g(20,10),g(1,1)) + g(1,2);
    return i;
}
