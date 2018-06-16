int g(int p){
  if (p<=1){
    return 1;
  } else {
    return 120;
  }
}

int f(){
    int a;
    a = 200;
    for (a = 0; a<123; a++){
  int b;
      a+= g(a);

    }
    return a;
}
