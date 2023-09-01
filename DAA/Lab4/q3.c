/*
    Given 2 integers x and n. Write a program to design your own
    power function to compute x^n with time complexity O9logn).
*/

#include <stdio.h>

int power(int x, int n) {
    int res = 1;
    if (x == 1 || n == 1)
        return x;
    else if (n == 0)
        return 1;
    else {
        while (n > 1) {
            if (n % 2 == 0)
                res *= x * x;
            else 
                res *= x * x * x;
            n /= 2;
        }
        return res;
    }
}

int main() {
    int x, n;
    printf("Enter an integer: ");
    scanf("%d", &x);
    printf("Enter power: ");
    scanf("%d", &n);

    printf("%d^%d = %d\n\n", x, n, power(x, n));
    return 0;
}
