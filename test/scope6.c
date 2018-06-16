int f()
{
    int i = 4;
    {
      int i = 3;
    }
    {
      int i = 8;
    }

    {
    {int i = 123;}
    }

    return i;
}
