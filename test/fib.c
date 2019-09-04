int fib(int n) {
    int result;
    if (n < 2) return n;
    result = fib(n-1) + fib(n-2);
    return result;
}

int main(void) {
    int n;
    n = input();
    output(fib(n));
    return 0;
}
