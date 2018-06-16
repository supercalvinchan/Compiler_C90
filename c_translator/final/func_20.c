int f(int p){
  if (p<=14){
    return 1;
  } else {
   return 10;
  }
}

int main(){
    int a;
    a = 200;
    for (a = 0; a<123; a++){
      int b;
      a+= f(a);
      while (a<20){
        ++a;
      }
    }
    return a;
}
