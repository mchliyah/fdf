int main()
{
    char a = 'c';
    int j = a;
    int i = 128;
    while (i / 2)
    {
        if (i / j)
        {
            printf("1");
        }
        else
        {
            printf("0");
            j = j / 2;
        }
        i = i / 2;
    }
    // if (i == 0)
    //     printf("0");
    // else
    //     printf("1");
    return (0);
}
