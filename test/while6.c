int f(){
  int i = 0;
  int j = 0;
  while((i < 10)||(i%3 == 7)){
    j = 0 ;
    while((j < 10)||(j<20)){
      j = j + 1;
    }
  i = i + 1;
  }
  return i+j;
}
