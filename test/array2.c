int f()
{
    int i;
    int a[5];
    a[0] = 9;
    a[1] = 10;
    a[3] = 7;
    a[4] = 6;
    a[2] = 9;

    for(i = 1; i < 3; ++i)
    {
       if(a[0] < a[i]){
           a[0] = a[i];
         }
    }
    return a[0];
}
