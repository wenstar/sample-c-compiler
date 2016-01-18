main()
{
    int i;
    int a[9];
    i = 0;
    while (i < 7) {
        a[i] = i;
        i = i + 1;
    }
    i = 0;
    while (i < 7) {
        print(a[i]);
        i = i + 1;
    }
}
