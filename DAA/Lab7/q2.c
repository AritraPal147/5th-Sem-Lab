/*
2) Write a program to find out the Longest Common 
Subsequence of two given strings. Calculate length 
of the LCS.

Input:
Enter the first string into an array: 10010101
Enter the second string into an array: 010110110

Output:
    LCS: 100110
    LCS Length: 6
*/

#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int mTable[MAX_LEN + 1][MAX_LEN + 1];  // Declaration of mTable

void printLCS(char X[], char Y[], int m, int n, char lcs[]) {
    int i = m, j = n, index = 0;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index] = X[i - 1];
            i--;
            j--;
            index++;
        } else if (mTable[i - 1][j] > mTable[i][j - 1])
            i--;
        else
            j--;
    }
    lcs[index] = '\0';

    // Reverse the LCS string
    int len = strlen(lcs);
    for (int k = 0; k < len / 2; k++) {
        char temp = lcs[k];
        lcs[k] = lcs[len - k - 1];
        lcs[len - k - 1] = temp;
    }
}

int lcsLength(char X[], char Y[], int m, int n) {
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                mTable[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                mTable[i][j] = mTable[i - 1][j - 1] + 1;
            else
                mTable[i][j] = max(mTable[i - 1][j], mTable[i][j - 1]);
        }
    }

    return mTable[m][n];
}

int main() {
    char X[MAX_LEN], Y[MAX_LEN];
    char lcs[MAX_LEN];

    printf("Enter the first string into an array: ");
    scanf("%s", X);

    printf("Enter the second string into an array: ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    int length = lcsLength(X, Y, m, n);

    printf("\nLCS: ");
    printLCS(X, Y, m, n, lcs);
    printf("%s\n", lcs);

    printf("LCS Length: %d\n", length);

    return 0;
}

