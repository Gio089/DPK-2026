#include <stdio.h>
#include <stdlib.h>

void kalikanMatriksVektor(int A[4][4], int X[4], int hasil[4]) {
    for (int i = 0; i < 4; i++) {
        hasil[i] = 0;
        for (int j = 0; j < 4; j++) {
            hasil[i] += A[i][j] * X[j];
        }
    }
}

int main() {
    int A[4][4];
    int X[4];
    int hasil[4];

    printf("Masukkan Elemen Matriks A (4x4)\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("Masukkan nilai matriks A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }
    printf("Hasil Input Matriks A:\n");
        printf("{ %d  %d  %d  %d }\n", A[0][0], A[0][1], A[0][2], A[0][3]);
        printf("{ %d  %d  %d  %d }\n", A[1][0], A[1][1], A[1][2], A[1][3]);
        printf("{ %d  %d  %d  %d }\n", A[2][0], A[2][1], A[2][2], A[2][3]);
        printf("{ %d  %d  %d  %d }\n", A[3][0], A[3][1], A[3][2], A[3][3]);

    printf("\nMasukkan Elemen Matriks X (4x1)\n");
    for (int i = 0; i < 4; i++) {
        printf("Masukkan nilai matriks X[%d]: ", i);
        scanf("%d", &X[i]);
    }
    printf("Hasil Input Matriks X:\n");
        printf("{ %d }\n", X[0]);
        printf("{ %d }\n", X[1]);
        printf("{ %d }\n", X[2]);
        printf("{ %d }\n", X[3]);

    kalikanMatriksVektor(A, X, hasil);

    printf("\nHasil Perkalian Matriks A x X:\n");
    for (int i = 0; i < 4; i++) {
        printf("[ %d ]\n", hasil[i]);
    }

    return 0;
}