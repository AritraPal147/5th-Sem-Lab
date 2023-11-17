#include <stdio.h>
#include <limits.h>
#define MAXSIZE 10

void printParenthesis(int i, int j, int n, int bracket[][MAXSIZE], char &name) {
    if (i == j) {
        printf("%c", name++);
        return;
    }

    printf("(");

    printParenthesis(i, bracket[i][j], n, bracket, name);
    printParenthesis(bracket[i][j] + 1, j, n, bracket, name);

    printf(")");
}

int matrixChainOrder(int dims[], int n) {
    int dp[n][n];
    int bracket[MAXSIZE][MAXSIZE];

    for (int i = 1; i < n; i++)
        dp[i][i] = 0;

    for (int cl = 2; cl < n; cl++) {
        for (int i = 1; i < n - cl + 1; i++) {
            int j = i + cl - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    bracket[i][j] = k;
                }
            }
        }
    }

    char name = 'A';
    printf("Optimal Parenthesization: ");
    printParenthesis(1, n - 1, n, bracket, name);
    printf("\n");

    return dp[1][n - 1];
}

int main() {
    int dims[] = {5, 4, 6, 2, 7};
    int n = sizeof(dims) / sizeof(dims[0]);

    int res = matrixChainOrder(dims, n);
    printf("Minimum number of scalar multiplications: %d\n", res);
    return 0;
}
