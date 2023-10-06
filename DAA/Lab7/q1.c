/*
1) Write a program to implement the matrix chain multiplication problem using 
M-table & S-table to find optimal parenthesization of a matrix-chain product. 
Print the number of scalar multiplications required for the given input.
Note# Dimensions of the matrices can be inputted as row and column values. 
Validate the dimension compatibility.

Input: 
Enter number of matrices: 4
Enter row and col size of A1: 30  35
Enter row and col size of A2: 35  15
Enter row and col size of A3: 15  5
Enter row and col size of A4: 5  10

Output:
M Table:
0    	15750  7875  	9375
0    	0      	2625  	4375
0    	0      	0      	750
0    	0      	0      	0
S Table:
0    	1      	1      	3
0    	0      	2      	3
0	    0      	0      	3
0    	0      	0      	0
Optimal parenthesization: ( ( A1   (A2   A3))   A4)
The optimal ordering of the given matrices requires 9375 scalar multiplications.
*/


#include <stdio.h>
#include <limits.h>

void matrixChainOrder(int p[], int n, int mTable[][n], int sTable[][n]) {
    for (int i = 1; i < n; i++)
        mTable[i][i] = 0;

    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            mTable[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++) {
                int cost = mTable[i][k] + mTable[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < mTable[i][j]) {
                    mTable[i][j] = cost;
                    sTable[i][j] = k;
                }
            }
        }
    }
}

void printOptimalParenthesis(int sTable[][5], int i, int j) {
    if (i == j)
        printf("A%d", i);
    else {
        printf("(");
        printOptimalParenthesis(sTable, i, sTable[i][j]);
        printOptimalParenthesis(sTable, sTable[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    int n;
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[n + 1];
    printf("Enter dimensions of matrices:\n");

    for (int i = 0; i < n; i++) {
        printf("Enter row and col size of A%d: ", i + 1);
        scanf("%d %d", &p[i], &p[i + 1]);
    }

    //for (int i = 1; i < n; i++) {
      //  if (p[i] <= 0 || p[i] != p[i + 1]) {
        //    printf("Invalid dimensions. Please enter positive and compatible dimensions.\n");
          //  return 1;
        //}
    //}

    int mTable[n + 1][n + 1], sTable[n + 1][n + 1];
    matrixChainOrder(p, n + 1, mTable, sTable);

    printf("M Table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            printf("%d\t\t", mTable[i][j]);
        printf("\n");
    }

    printf("S Table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            printf("%d\t\t", sTable[i][j]);
        printf("\n");
    }

    printf("Optimal parenthesization: ");
    printOptimalParenthesis(sTable, 1, n);
    printf("\n");

    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", mTable[1][n]);

    return 0;
}


