#include <stdio.h>

void EXCHANGE(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

void ROTATE_RIGHT(int p1[], int p2) {
    if (p2 <= 0) {
        printf("Invalid rotation count.\n");
        return;
    }

    int last = p1[p2 - 1];
    for (int i = p2 - 2; i >= 0; --i) {
        p1[i + 1] = p1[i];
    }
    p1[0] = last;
}

int main() {
    int N;
    printf("Enter the size of the array: ");
    scanf("%d", &N);

    int A[N];
    printf("Enter the array elements: ");
    for (int i = 0; i < N; ++i) {
        scanf("%d", &A[i]);
    }

    int p2;
    printf("Enter the number of elements to rotate: ");
    scanf("%d", &p2);

    if (p2 < 1 || p2 > N) {
        printf("Invalid number of elements to rotate.\n");
        return 1;
    }

    printf("Before ROTATE:\t");
    for (int i = 0; i < N; ++i) {
        printf("%d ", A[i]);
    }
    printf("\n");

    ROTATE_RIGHT(A, p2);

    printf("After  ROTATE:\t");
    for (int i = 0; i < N; ++i) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
