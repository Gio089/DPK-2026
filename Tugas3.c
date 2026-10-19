#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    char A[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    int baris, kolom, z = 0, ada_pemenang = 0;
    char pemenang_simbol = ' ';

    while (z < 9) {
        printf("\nGiliran ke %d \n", z + 1);
        
        if (z % 2 == 0) {
            do {
                printf("Baris Pemain 1 (0-2): ");
                scanf("%d", &baris);
                printf("Kolom Pemain 1 (0-2): ");
                scanf("%d", &kolom);
                
                if (baris < 0 || baris > 2 || kolom < 0 || kolom > 2) {
                    printf("Input tidak valid! Koordinat harus antara 0 sampai 2.\n\n");
                } else if (A[baris][kolom] != ' ') {
                    printf("Kotak sudah terisi! Silakan pilih koordinat lain.\n\n");
                }
            } while (baris < 0 || baris > 2 || kolom < 0 || kolom > 2 || A[baris][kolom] != ' ');
            
            A[baris][kolom] = 'X';
        } else {
            do {
                printf("Baris Pemain 2 (0-2): ");
                scanf("%d", &baris);
                printf("Kolom Pemain 2 (0-2): ");
                scanf("%d", &kolom);
                
                if (baris < 0 || baris > 2 || kolom < 0 || kolom > 2) {
                    printf("Input tidak valid! Koordinat harus antara 0 sampai 2.\n\n");
                } else if (A[baris][kolom] != ' ') {
                    printf("Kotak sudah terisi! Silakan pilih koordinat lain.\n\n");
                }
            } while (baris < 0 || baris > 2 || kolom < 0 || kolom > 2 || A[baris][kolom] != ' ');
            
            A[baris][kolom] = 'O';
        }

        printf("Kondisi Papan Saat Ini:\n");
        printf(" %c | %c | %c \n", A[0][0], A[0][1], A[0][2]);
        printf(" %c | %c | %c \n", A[1][0], A[1][1], A[1][2]);
        printf(" %c | %c | %c \n", A[2][0], A[2][1], A[2][2]);

        // 1. Cek 3 Baris Horizontal
        for (int i = 0; i < 3; i++) {
            if (A[i][0] == A[i][1] && A[i][1] == A[i][2] && A[i][0] != ' ') {
                ada_pemenang = 1;
                pemenang_simbol = A[i][0];
            }
        }

        // 2. Cek 3 Kolom Vertikal
        for (int i = 0; i < 3; i++) {
            if (A[0][i] == A[1][i] && A[1][i] == A[2][i] && A[0][i] != ' ') {
                ada_pemenang = 1;
                pemenang_simbol = A[0][i];
            }
        }

        // 3. Cek Diagonal Utama (\)
        if (A[0][0] == A[1][1] && A[1][1] == A[2][2] && A[0][0] != ' ') {
            ada_pemenang = 1;
            pemenang_simbol = A[0][0];
        }

        // 4. Cek Diagonal Terbalik (/)
        if (A[0][2] == A[1][1] && A[1][1] == A[2][0] && A[0][2] != ' ') { 
            ada_pemenang = 1;
            pemenang_simbol = A[0][2];
        }

        // Jika ada yang menang, loop berhenti
        if (ada_pemenang == 1) {
            break;
        }

        z++;
    }

    printf("\n=== HASIL AKHIR PERMAINAN ===\n");
    if (ada_pemenang == 1) {
        if (pemenang_simbol == 'X') {
            printf("Selamat! Pemain 1 (X) Menang!\n");
        } else {
            printf("Selamat! Pemain 2 (O) Menang!\n");
        }
    } else {
        printf("Tidak Ada Pemenang, Permainan Seri!\n");
    }

    return 0;
}
