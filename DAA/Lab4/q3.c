/*
    Given 2 integers x and n. Write a program to design your own
    power function to compute x^n with time complexity O(logn).
*/

#include <stdio.h>

int power(int x, int n) {
    if (n == 0) 
        return 1.0;
    else if (n % 2 == 0) {
        double temp = power(x, n / 2);
        return temp * temp;
    } else {
        double temp = power(x, (n - 1) / 2);
        return x * temp * temp;
    }
}

int main() {
    int x, n;
    printf("Enter an integer: ");
    scanf("%d", &x);
    printf("Enter power: ");
    scanf("%d", &n);

    printf("\n%d^%d = %d\n\n", x, n, power(x, n));
    return 0;
}
