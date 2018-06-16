int f(int g)
{
    if (g < 2) {
        return 1;
    } else {
        return g + f(g - 1);
    }
}
