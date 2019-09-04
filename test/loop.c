void main(void) {
    int a[10];
    int i;
    int sum;
    sum = 0;
    a[0] = 0;
    a[1] = 1;
    i = 2;
    while (i < 10) {
        a[i] = a[i-1] + a[i-2];
        i = i + 1;
    }
    i = 0;
    while (i < 10) {
        output(a[i]);
        i = i + 1;
    }
    i = 1;
    while (i <= 500) {
        sum = sum + i;
        i = i + 1;
    }
    output(sum);
    return;
}
