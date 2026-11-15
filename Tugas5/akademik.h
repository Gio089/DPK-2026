#ifndef AKADEMIK_H
#define AKADEMIK_H

// Tabel Mata Kuliah
typedef struct matakuliah_t {
    char kode_mk[10];
    char nama_mk[50];
    int sks;
} Matakuliah;

// Tabel Mahasiswa
typedef struct mahasiswa_t {
    char nim[10];
    char nama[50];
    char jurusan[50];
} Mahasiswa;

// Tabel KRS
typedef struct krs_t {
    char kode_mk[10];
    char nim[10];
} KRS;

// Deklarasi fungsi
void input_data_mk(Matakuliah *mk, int jumlah_mk);
void input_data_mhs(Mahasiswa *mhs, int jumlah_mhs);
void input_krs(KRS *krs, int jumlah_krs,
               Mahasiswa *mhs, int jumlah_mhs,
               Matakuliah *mk, int jumlah_mk);

#endif
