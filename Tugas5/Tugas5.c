#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "akademik.h"

Matakuliah matakuliah[50];
Mahasiswa mahasiswa[100];
KRS krs[500];


void input_data_mk(Matakuliah *mk, int jumlah_mk) {

    for (int i = 0; i < jumlah_mk; i++) {

        printf("\nMata Kuliah ke-%d\n", i + 1);

        printf("Kode MK : ");
        scanf("%9s", mk[i].kode_mk);

        printf("Nama MK : ");
        scanf(" %49[^\n]", mk[i].nama_mk);

        printf("SKS     : ");
        scanf("%d", &mk[i].sks);
    }
}


void input_data_mhs(Mahasiswa *mhs, int jumlah_mhs) {

    for (int i = 0; i < jumlah_mhs; i++) {

        printf("\nMahasiswa ke-%d\n", i + 1);

        printf("NIM     : ");
        scanf("%9s", mhs[i].nim);

        printf("Nama    : ");
        scanf(" %49[^\n]", mhs[i].nama);

        printf("Jurusan : ");
        scanf(" %49[^\n]", mhs[i].jurusan);
    }
}


void input_krs(KRS *krs, int jumlah_krs,
               Mahasiswa *mhs, int jumlah_mhs,
               Matakuliah *mk, int jumlah_mk) {

    int pilih_mhs, pilih_mk;

    for (int i = 0; i < jumlah_krs; i++) {

        printf("\n=== INPUT KRS KE-%d ===\n", i + 1);

        printf("\nDAFTAR MAHASISWA\n");

        for (int j = 0; j < jumlah_mhs; j++) {

            printf("%d. %s - %s\n",
                   j + 1,
                   mhs[j].nim,
                   mhs[j].nama);
        }

        printf("Pilih mahasiswa: ");
        scanf("%d", &pilih_mhs);

        if (pilih_mhs < 1 || pilih_mhs > jumlah_mhs) {

            printf("Pilihan mahasiswa tidak valid!\n");
            i--;
            continue;
        }

        strcpy(krs[i].nim,
               mhs[pilih_mhs - 1].nim);

        printf("\nDAFTAR MATA KULIAH\n");

        for (int j = 0; j < jumlah_mk; j++) {

            printf("%d. %s - %s (%d SKS)\n",
                   j + 1,
                   mk[j].kode_mk,
                   mk[j].nama_mk,
                   mk[j].sks);
        }

        printf("Pilih mata kuliah: ");
        scanf("%d", &pilih_mk);

        if (pilih_mk < 1 || pilih_mk > jumlah_mk) {

            printf("Pilihan mata kuliah tidak valid!\n");
            i--;
            continue;
        }

        strcpy(krs[i].kode_mk,
               mk[pilih_mk - 1].kode_mk);
    }
}

int main() {
    int jumlah_mk, jumlah_mhs, jumlah_krs;

    // INPUT MATA KULIAH
    printf("=== INPUT DATA MATA KULIAH ===\n");

    printf("Jumlah mata kuliah: ");
    scanf("%d", &jumlah_mk);

    if (jumlah_mk < 1 || jumlah_mk > 50) {
        printf("Jumlah mata kuliah tidak valid!\n");
        return 1;
    }

    input_data_mk(matakuliah, jumlah_mk);


    // INPUT MAHASISWA
    printf("\n=== INPUT DATA MAHASISWA ===\n");

    printf("Jumlah mahasiswa: ");
    scanf("%d", &jumlah_mhs);

    if (jumlah_mhs < 1 || jumlah_mhs > 100) {
        printf("Jumlah mahasiswa tidak valid!\n");
        return 1;
    }

    input_data_mhs(mahasiswa, jumlah_mhs);


    // INPUT KRS
    printf("\n=== INPUT DATA KRS ===\n");

    printf("Jumlah data KRS: ");
    scanf("%d", &jumlah_krs);

    if (jumlah_krs < 1 || jumlah_krs > 500) {
        printf("Jumlah KRS tidak valid!\n");
        return 1;
    }

    input_krs(krs, jumlah_krs,
              mahasiswa, jumlah_mhs,
              matakuliah, jumlah_mk);

    // Tampilkan Tabel KRS
    printf("========================================\n");
    printf("               TABEL KRS\n");
    printf("========================================\n");

    printf("%-15s %-15s\n", "KODE MK", "NIM");

    printf("----------------------------------------\n");

    for (int i = 0; i < jumlah_krs; i++) {

        printf("%-15s %-15s\n",
               krs[i].kode_mk,
               krs[i].nim);
    }

    printf("========================================\n");

    return 0;
}
