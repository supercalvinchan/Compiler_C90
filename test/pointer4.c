int f(){
  int l;
  int* p;
  int* d;
  l = 123;
  p = &l;
  d = p;
  {
    p = &l;
    {
      *d = 5;
      return l;
    }
  }
}
