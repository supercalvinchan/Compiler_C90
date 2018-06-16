int f()
{
    int n[ 8];
     int i;

     for ( i = 0; i < 8; i++ ) {
        n[ i ] = i + 3;
     }

     return n[3]||n[2];

}
