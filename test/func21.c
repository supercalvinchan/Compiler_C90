int l(){
  return 12;
}


int g(int p){
  if (p<=14){
    return 1;
  } else {
    return 10 + l();
  }
}

int f(){
    int a;
    a = 200;
    for (a = 0; a<123; a++){
        int b;
      a+= g(a);
      while (a<20){
        ++a;
      }
    }
    return a;
}
