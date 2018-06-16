int l(){
  return 12;
}


int g(int p, int d){
  if (p<=14){
    return 1;
  } else {
    return 10 + l() + d;
  }
}

int f(){
    int a;
    int b;
    a = 200;
    for (a = 0; a<123; a++){
      a+= g(a,7);
      b = g(-2,-3);
      while (a<20){
        ++a;
        break;
      }
    }
    return a+b;
}
