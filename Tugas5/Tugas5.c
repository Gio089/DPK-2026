
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
    int total_sks, duplikat;
    int i = 0;
    while (i < jumlah_krs) {
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
            continue;
        }

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
            continue;
        }

        // SUPAYA MATA KULIAH YG DIPILIH TIDAK DOUBLE
        duplikat = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(krs[j].nim,
                       mhs[pilih_mhs - 1].nim) == 0 &&
                strcmp(krs[j].kode_mk,
                       mk[pilih_mk - 1].kode_mk) == 0) {
                duplikat = 1;
                break;
            }
        }
        if (duplikat == 1) {
            printf("\nMata kuliah sudah diambil mahasiswa tersebut!\n");
            printf("Silakan pilih kembali.\n");
            continue;
        }

        // SUPAYA MAKSIMAL 24 SKS
        total_sks = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(krs[j].nim,
                       mhs[pilih_mhs - 1].nim) == 0) {
                for (int k = 0; k < jumlah_mk; k++) {
                    if (strcmp(krs[j].kode_mk,
                               mk[k].kode_mk) == 0) {
                        total_sks += mk[k].sks;
                        break;
                    }
                }
            }
        }

        if (total_sks + mk[pilih_mk - 1].sks > 24) {
            printf("\nPengambilan mata kuliah melebihi 24 SKS!\n");
            printf("Total SKS saat ini: %d\n", total_sks);
            printf("Silakan pilih mata kuliah lain.\n");
            continue;
        }

        strcpy(krs[i].nim,
               mhs[pilih_mhs - 1].nim);
        strcpy(krs[i].kode_mk,
               mk[pilih_mk - 1].kode_mk);

        printf("\nData KRS berhasil ditambahkan!\n");
        i++;
    }
}


int main() {
    int jumlah_mk, jumlah_mhs, jumlah_krs;
 
    printf("=== INPUT DATA MATA KULIAH ===\n");
    printf("Jumlah mata kuliah: ");
    scanf("%d", &jumlah_mk);
    if (jumlah_mk < 1 || jumlah_mk > 50) {
        printf("Jumlah mata kuliah tidak valid!\n");
        return 1;
    }
    input_data_mk(matakuliah, jumlah_mk);

    printf("\n=== INPUT DATA MAHASISWA ===\n");
    printf("Jumlah mahasiswa: ");
    scanf("%d", &jumlah_mhs);
    if (jumlah_mhs < 1 || jumlah_mhs > 100) {
        printf("Jumlah mahasiswa tidak valid!\n");
        return 1;
    }
    input_data_mhs(mahasiswa, jumlah_mhs);

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


    // MENAMPILKAN TABEL MATA KULIAH
    printf("\n========================================\n");
    printf("          TABEL MATA KULIAH\n");
    printf("========================================\n");
    printf("%-12s %-25s %-5s\n",
           "KODE MK", "NAMA MK", "SKS");
    for (int i = 0; i < jumlah_mk; i++) {
        printf("%-12s %-25s %-5d\n",
               matakuliah[i].kode_mk,
               matakuliah[i].nama_mk,
               matakuliah[i].sks);
    }

    // MENAMPILKAN TABEL MAHASISWA
    printf("\n========================================\n");
    printf("           TABEL MAHASISWA\n");
    printf("========================================\n");
    printf("%-12s %-20s %-20s\n",
           "NIM", "NAMA", "JURUSAN");
    for (int i = 0; i < jumlah_mhs; i++) {
        printf("%-12s %-20s %-20s\n",
               mahasiswa[i].nim,
               mahasiswa[i].nama,
               mahasiswa[i].jurusan);
    }

    // MENAMPILKAN TABEL KRS
    printf("\n========================================\n");
    printf("                TABEL KRS\n");
    printf("========================================\n");
    printf("%-15s %-15s\n",
           "KODE MK", "NIM");
    for (int i = 0; i < jumlah_krs; i++) {
        printf("%-15s %-15s\n",
               krs[i].kode_mk,
               krs[i].nim);
    }

    return 0;
}
