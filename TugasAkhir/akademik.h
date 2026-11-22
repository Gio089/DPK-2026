#ifndef AKADEMIK_H
#define AKADEMIK_H

#define MAKS_NAMA 50
#define MAKS_NIM 20
#define MAKS_KODE 15
#define MAKS_JURUSAN 50
#define BATAS_SKS 24

typedef struct mahasiswa { //mahasiswa sebagai variabel supaya bisa panggil dirinya sendiri
    char nim[MAKS_NIM];
    char nama[MAKS_NAMA];
    char jurusan[MAKS_JURUSAN];
    struct mahasiswa *next;
} Mahasiswa; //nama alias untuk struct mahasiswa = Mahasiswa (spt jadi tipe data baru)

typedef struct {
    char nim[MAKS_NIM];
    char nama[MAKS_NAMA];
    char jurusan[MAKS_JURUSAN];
} DataMahasiswa;

typedef struct matakuliah {
    char kode_mk[MAKS_KODE];
    char nama_mk[MAKS_NAMA];
    int sks;
    struct matakuliah *next;
} Matakuliah;

typedef struct {
    char kode_mk[MAKS_KODE];
    char nama_mk[MAKS_NAMA];
    int sks;
} DataMatakuliah;

typedef struct krs {
    char nim[MAKS_NIM];
    char kode_mk[MAKS_KODE];
    struct krs *next;
} KRS;

typedef struct {
    char nim[MAKS_NIM];
    char kode_mk[MAKS_KODE];
} DataKRS;

extern Mahasiswa *headMhs;
extern Matakuliah *headMK;
extern KRS *headKRS;

void input_data_mhs(void);
void tampil_data_mhs(void);
void hapus_data_mhs(void);
void update_data_mhs(void);
void simpan_data_mhs(void);
void load_data_mhs(void);
Mahasiswa *cari_mhs(char *nim);

void input_data_mk(void);
void tampil_data_mk(void);
void hapus_data_mk(void);
void update_data_mk(void);
void simpan_data_mk(void);
void load_data_mk(void);
Matakuliah *cari_mk(char *kode);

void input_krs(void);
void tampil_data_krs(void);
void hapus_data_krs(void);
void update_data_krs(void);
void simpan_data_krs(void);
void load_data_krs(void);

void tampilkan_semua_data(void);
void load_semua_data(void);
void bebaskan_semua_data(void);

#endif
