int f(int p){
  if (p<=1){
    return 1;
  } else {
    return 120;
  }
}

int main(){
    int a;
    a = 200;
    for (a = 0; a<123; a++){
      int b;
      a+= f(a);
    }
    return a;
}
