int f()
{
  int i, j, temp;
  int arr[5];
  arr[0] = 2;
  arr[1] = -2;
  arr[3] = 7;
  arr[4] = 8;
  arr[2] = 9;
   for (i = 0; i < (6-1); ++i)
   {
        for (j = 0; j < 7 - 3 - i; ++j )
        {
             if (arr[j] > arr[j+1])
             {
                  temp = arr[j+1];
                  arr[j+1] = arr[j];
                  arr[j] = temp;
             }
        }
   }
   return arr[1];

}
