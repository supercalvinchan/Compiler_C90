int x;

int f()
{
    int y;
    x=x+1;
    return x;
}

int main()
{
    return f()+f();
}
