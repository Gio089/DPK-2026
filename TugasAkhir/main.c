#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "akademik.h"

Mahasiswa *headMhs = NULL; //variabel pointer headMhs bertipe data Mahasiswa
Matakuliah *headMK = NULL;
KRS *headKRS = NULL;

//Input teks dengan spasi 
static void baca_teks(char *tujuan, int ukuran) {
    if (fgets(tujuan, ukuran, stdin) != NULL) //if memastikan input dari keyboard berhasil
        tujuan[strcspn(tujuan, "\n")] = '\0'; //buang newline dari fgets
}

Mahasiswa *cari_mhs(char *nim) {
    Mahasiswa *bantu = headMhs; //supaya data node awal2 tetap bisa diakses
    while (bantu != NULL) { //kalau daftar mahasiswa kosong, perulangan stop
        if (strcmp(bantu->nim, nim) == 0) return bantu; //bantu->nim = ambil nilai nim yg tersimpan dalam alamat yg ditunjuk bantu
        bantu = bantu->next; //bantu->next = ambil alamat node selanjutnya yg tersimpan dalam alamat yang ditunjuk bantu
    }
    return NULL; //hasilkan NULL ketika selesai terpanggil di main
}

void input_data_mhs(void) { // (void) = tidak menerima parameter apapun saat dipanggil
    Mahasiswa *baru, *bantu;
    char nim[MAKS_NIM];

    printf("\n=== TAMBAH DATA MAHASISWA ===\n");
    printf("NIM     : ");
    baca_teks(nim, sizeof(nim));

    if (nim[0] == '\0') {
        printf("NIM tidak boleh kosong.\n");
        return;
    }
    if (cari_mhs(nim) != NULL) {
        printf("NIM sudah terdaftar.\n");
        return;
    }

    baru = (Mahasiswa *)malloc(sizeof(Mahasiswa));// pesan memori untuk baru
    if (baru == NULL) { //kalau ram penuh = fungsi berhenti, kembali ke menu utama
        printf("Memori tidak cukup.\n");
        return;
    }

    strcpy(baru->nim, nim);
    printf("Nama    : ");
    baca_teks(baru->nama, sizeof(baru->nama));
    printf("Jurusan : ");
    baca_teks(baru->jurusan, sizeof(baru->jurusan));

    if (baru->nama[0] == '\0' || baru->jurusan[0] == '\0') {
        printf("Nama dan jurusan tidak boleh kosong.\n");
        free(baru);
        return;
    }

    baru->next = NULL;
    if (headMhs == NULL) {
        headMhs = baru;
    } else {
        bantu = headMhs;
        while (bantu->next != NULL) bantu = bantu->next;
        bantu->next = baru;
    }

    simpan_data_mhs();
    printf("Data mahasiswa berhasil ditambahkan dan disimpan.\n");
}

void tampil_data_mhs(void) {
    Mahasiswa *bantu = headMhs;
    int nomor = 0;

    printf("\n================ DAFTAR MAHASISWA ================\n");
    printf("%-4s %-18s %-25s %-25s\n", "No", "NIM", "Nama", "Jurusan");
    while (bantu != NULL) {
        printf("%-4d %-18s %-25s %-25s\n",
               ++nomor, bantu->nim, bantu->nama, bantu->jurusan);
        bantu = bantu->next;
    }
    if (nomor == 0) printf("Belum ada data mahasiswa.\n");
}

void hapus_data_mhs(void) {
    char nim[MAKS_NIM];
    Mahasiswa *bantu, *sebelumnya = NULL;
    KRS *cek;

    printf("\n=== HAPUS DATA MAHASISWA ===\n");

    if (headMhs == NULL) {
        printf("Belum ada data mahasiswa.\n");
        return;
    }

    tampil_data_mhs();

    printf("\nMasukkan NIM mahasiswa yang ingin dihapus: ");
    baca_teks(nim, sizeof(nim));

    bantu = headMhs;

    while (bantu != NULL && strcmp(bantu->nim, nim) != 0) {
        sebelumnya = bantu;
        bantu = bantu->next;
    }

    if (bantu == NULL) {
        printf("Data mahasiswa tidak ditemukan.\n");
        return;
    }

    cek = headKRS;
    while (cek != NULL) { //kalau punya KRS, mhs tidak bisa dihapus
        if (strcmp(cek->nim, nim) == 0) {
            printf("Mahasiswa masih memiliki data KRS.\n");
            printf("Hapus KRS mahasiswa terlebih dahulu.\n");
            return;
        }
        cek = cek->next;
    }

    if (sebelumnya == NULL) {
        headMhs = bantu->next;
    } else {
        sebelumnya->next = bantu->next;
    }

    free(bantu);

    simpan_data_mhs();

    printf("Data mahasiswa berhasil dihapus.\n");
}

void simpan_data_mhs(void) {
    FILE *fp = fopen("mahasiswa.txt", "w");
    Mahasiswa *bantu = headMhs;

    if (fp == NULL) {
        printf("Gagal membuka mahasiswa.txt untuk penyimpanan.\n");
        return;
    }

    while (bantu != NULL) {
        fprintf(fp, "%s|%s|%s\n", bantu->nim, bantu->nama, bantu->jurusan);
        bantu = bantu->next;
    }
    fclose(fp);
}

void load_data_mhs(void) {
    FILE *fp = fopen("mahasiswa.txt", "r");
    char baris[MAKS_NIM + MAKS_NAMA + MAKS_JURUSAN + 3];
    DataMahasiswa data;
    Mahasiswa *baru, *bantu;

    if (fp == NULL) return;

    while (fgets(baris, sizeof(baris), fp) != NULL) {
        if (sscanf(baris, "%19[^|]|%49[^|]|%49[^\n]",
                   data.nim, data.nama, data.jurusan) != 3) continue;
        if (cari_mhs(data.nim) != NULL) continue;

        baru = (Mahasiswa *)malloc(sizeof(Mahasiswa));
        if (baru == NULL) {
            printf("Memori tidak cukup saat memuat mahasiswa.\n");
            break;
        }
        strcpy(baru->nim, data.nim);
        strcpy(baru->nama, data.nama);
        strcpy(baru->jurusan, data.jurusan);
        baru->next = NULL;

        if (headMhs == NULL) headMhs = baru;
        else {
            bantu = headMhs;
            while (bantu->next != NULL) bantu = bantu->next;
            bantu->next = baru;
        }
    }
    fclose(fp);
}

Matakuliah *cari_mk(char *kode) {
    Matakuliah *bantu = headMK;
    while (bantu != NULL) {
        if (strcmp(bantu->kode_mk, kode) == 0) return bantu;
        bantu = bantu->next;
    }
    return NULL;
}

void input_data_mk(void) {
    Matakuliah *baru, *bantu;
    char kode[MAKS_KODE];
    int hasil;

    printf("\n=== TAMBAH DATA MATA KULIAH ===\n");
    printf("Kode MK : ");
    baca_teks(kode, sizeof(kode));

    if (kode[0] == '\0') {
        printf("Kode mata kuliah tidak boleh kosong.\n");
        return;
    }
    if (cari_mk(kode) != NULL) {
        printf("Kode mata kuliah sudah terdaftar.\n");
        return;
    }

    baru = (Matakuliah *)malloc(sizeof(Matakuliah));
    if (baru == NULL) {
        printf("Memori tidak cukup.\n");
        return;
    }

    strcpy(baru->kode_mk, kode);
    printf("Nama MK : ");
    baca_teks(baru->nama_mk, sizeof(baru->nama_mk));

    printf("SKS     : ");
    hasil = scanf("%d", &baru->sks);
    while (getchar() != '\n' && !feof(stdin)) {}
    if (hasil != 1 || baru->sks < 1 || baru->sks > 6) {
        printf("SKS harus berupa angka 1 sampai 6.\n");
        free(baru);
        return;
    }
    if (baru->nama_mk[0] == '\0') {
        printf("Nama mata kuliah tidak boleh kosong.\n");
        free(baru);
        return;
    }

    baru->next = NULL;
    if (headMK == NULL) headMK = baru;
    else {
        bantu = headMK;
        while (bantu->next != NULL) bantu = bantu->next;
        bantu->next = baru;
    }

    simpan_data_mk();
    printf("Mata kuliah berhasil ditambahkan dan disimpan.\n");
}

void tampil_data_mk(void) {
    Matakuliah *bantu = headMK;
    int nomor = 0;

    printf("\n================ DAFTAR MATA KULIAH ================\n");
    printf("%-4s %-15s %-30s %-5s\n", "No", "Kode MK", "Nama MK", "SKS");
    while (bantu != NULL) {
        printf("%-4d %-15s %-30s %-5d\n",
               ++nomor, bantu->kode_mk, bantu->nama_mk, bantu->sks);
        bantu = bantu->next;
    }
    if (nomor == 0) printf("Belum ada data mata kuliah.\n");
}

void hapus_data_mk(void) {
    char kode[MAKS_KODE];
    Matakuliah *bantu, *sebelumnya = NULL;
    KRS *cek;

    printf("\n=== HAPUS DATA MATA KULIAH ===\n");

    if (headMK == NULL) {
        printf("Belum ada data mata kuliah.\n");
        return;
    }

    tampil_data_mk();

    printf("\nMasukkan kode mata kuliah yang ingin dihapus: ");
    baca_teks(kode, sizeof(kode));

    bantu = headMK;

    while (bantu != NULL && strcmp(bantu->kode_mk, kode) != 0) {
        sebelumnya = bantu;
        bantu = bantu->next;
    }

    if (bantu == NULL) {
        printf("Mata kuliah tidak ditemukan.\n");
        return;
    }

    cek = headKRS;
    while (cek != NULL) {
        if (strcmp(cek->kode_mk, kode) == 0) {
            printf("Mata kuliah masih digunakan dalam data KRS.\n");
            printf("Hapus KRS terkait terlebih dahulu.\n");
            return;
        }
        cek = cek->next;
    }

    if (sebelumnya == NULL) {
        headMK = bantu->next;
    } else {
        sebelumnya->next = bantu->next;
    }

    free(bantu);

    simpan_data_mk();

    printf("Data mata kuliah berhasil dihapus.\n");
}

void simpan_data_mk(void) {
    FILE *fp = fopen("matakuliah.txt", "w");
    Matakuliah *bantu = headMK;

    if (fp == NULL) {
        printf("Gagal membuka matakuliah.txt untuk penyimpanan.\n");
        return;
    }

    while (bantu != NULL) {
        fprintf(fp, "%s|%s|%d\n", bantu->kode_mk, bantu->nama_mk, bantu->sks);
        bantu = bantu->next;
    }
    fclose(fp);
}

void load_data_mk(void) {
    FILE *fp = fopen("matakuliah.txt", "r");
    char baris[MAKS_KODE + MAKS_NAMA + 20];
    DataMatakuliah data;
    Matakuliah *baru, *bantu;

    if (fp == NULL) return;

    while (fgets(baris, sizeof(baris), fp) != NULL) {
        if (sscanf(baris, "%14[^|]|%49[^|]|%d",
                   data.kode_mk, data.nama_mk, &data.sks) != 3) continue;
        if (cari_mk(data.kode_mk) != NULL) continue;

        baru = (Matakuliah *)malloc(sizeof(Matakuliah));
        if (baru == NULL) {
            printf("Memori tidak cukup saat memuat mata kuliah.\n");
            break;
        }
        strcpy(baru->kode_mk, data.kode_mk);
        strcpy(baru->nama_mk, data.nama_mk);
        baru->sks = data.sks;
        baru->next = NULL;

        if (headMK == NULL) headMK = baru;
        else {
            bantu = headMK;
            while (bantu->next != NULL) bantu = bantu->next;
            bantu->next = baru;
        }
    }
    fclose(fp);
}

static int krs_sudah_ada(char *nim, char *kode) {
    KRS *bantu = headKRS;
    while (bantu != NULL) {
        if (strcmp(bantu->nim, nim) == 0 &&
            strcmp(bantu->kode_mk, kode) == 0) return 1;
        bantu = bantu->next;
    }
    return 0;
}

static int hitung_total_sks(char *nim) {
    KRS *bantu = headKRS;
    int total = 0;
    while (bantu != NULL) {
        if (strcmp(bantu->nim, nim) == 0) {
            Matakuliah *mk = cari_mk(bantu->kode_mk);
            if (mk != NULL) total += mk->sks;
        }
        bantu = bantu->next;
    }
    return total;
}

void input_krs(void) {
    char nim[MAKS_NIM], kode[MAKS_KODE];
    Mahasiswa *mhs;
    Matakuliah *mk;
    KRS *baru, *bantu;
    int total;

    printf("\n=== TAMBAH DATA KRS ===\n");
    if (headMhs == NULL || headMK == NULL) {
        printf("Tambahkan data mahasiswa dan mata kuliah terlebih dahulu.\n");
        return;
    }

    tampil_data_mhs();
    printf("\nMasukkan NIM mahasiswa: ");
    baca_teks(nim, sizeof(nim));
    mhs = cari_mhs(nim);
    if (mhs == NULL) {
        printf("NIM tidak ditemukan.\n");
        return;
    }

    tampil_data_mk();
    printf("\nMasukkan kode mata kuliah: ");
    baca_teks(kode, sizeof(kode));
    mk = cari_mk(kode);
    if (mk == NULL) {
        printf("Kode mata kuliah tidak ditemukan.\n");
        return;
    }

    if (krs_sudah_ada(nim, kode)) {
        printf("Mahasiswa tersebut sudah mengambil mata kuliah ini.\n");
        return;
    }

    total = hitung_total_sks(nim);
    if (total + mk->sks > BATAS_SKS) {
        printf("KRS ditolak. Total SKS akan menjadi %d, melebihi batas %d SKS.\n",
               total + mk->sks, BATAS_SKS);
        printf("Total SKS mahasiswa saat ini: %d\n", total);
        return;
    }

    baru = (KRS *)malloc(sizeof(KRS));
    if (baru == NULL) {
        printf("Memori tidak cukup.\n");
        return;
    }

    strcpy(baru->nim, nim);
    strcpy(baru->kode_mk, kode);
    baru->next = NULL;

    if (headKRS == NULL) headKRS = baru;
    else {
        bantu = headKRS;
        while (bantu->next != NULL) bantu = bantu->next;
        bantu->next = baru;
    }

    simpan_data_krs();
    printf("KRS berhasil ditambahkan dan disimpan.\n");
}

void tampil_data_krs(void) {
    KRS *bantu = headKRS;
    int nomor = 0;

    printf("\n================ DAFTAR KRS ================\n");
    printf("%-4s %-18s %-15s %-25s\n",
           "No", "NIM", "Kode MK", "Nama Mata Kuliah");
    while (bantu != NULL) {
        Mahasiswa *mhs = cari_mhs(bantu->nim);
        Matakuliah *mk = cari_mk(bantu->kode_mk);
        printf("%-4d %-18s %-15s %-25s\n",
               ++nomor, bantu->nim, bantu->kode_mk,
               mk != NULL ? mk->nama_mk : "(MK tidak ditemukan)");
        if (mhs == NULL) {
            // Menandai bahwa NIM pada file KRS tidak cocok dengan data mahasiswa.
            printf("     (Data mahasiswa untuk NIM ini tidak ditemukan)\n");
        }
        bantu = bantu->next;
    }
    if (nomor == 0) printf("Belum ada data KRS.\n");
}

void hapus_data_krs(void) {
    char nim[MAKS_NIM];
    char kode[MAKS_KODE];
    KRS *bantu, *sebelumnya = NULL;

    printf("\n=== HAPUS DATA KRS ===\n");

    if (headKRS == NULL) {
        printf("Belum ada data KRS.\n");
        return;
    }

    tampil_data_krs();

    printf("\nMasukkan NIM mahasiswa: ");
    baca_teks(nim, sizeof(nim));

    printf("Masukkan kode mata kuliah: ");
    baca_teks(kode, sizeof(kode));

    bantu = headKRS;

    while (bantu != NULL) {
        if (strcmp(bantu->nim, nim) == 0 &&
            strcmp(bantu->kode_mk, kode) == 0) {
            break;
        }

        sebelumnya = bantu;
        bantu = bantu->next;
    }

    if (bantu == NULL) {
        printf("Data KRS tidak ditemukan.\n");
        return;
    }

    if (sebelumnya == NULL) {
        headKRS = bantu->next;
    } else {
        sebelumnya->next = bantu->next;
    }

    free(bantu);

    simpan_data_krs();

    printf("Data KRS berhasil dihapus.\n");
}

void simpan_data_krs(void) {
    FILE *fp = fopen("krs.txt", "w");
    KRS *bantu = headKRS;

    if (fp == NULL) {
        printf("Gagal membuka krs.txt untuk penyimpanan.\n");
        return;
    }

    while (bantu != NULL) {
        fprintf(fp, "%s|%s\n", bantu->nim, bantu->kode_mk);
        bantu = bantu->next;
    }
    fclose(fp);
}

void load_data_krs(void) {
    FILE *fp = fopen("krs.txt", "r");
    char baris[MAKS_NIM + MAKS_KODE + 2];
    DataKRS data;
    KRS *baru, *bantu;

    if (fp == NULL) return;

    while (fgets(baris, sizeof(baris), fp) != NULL) {
        if (sscanf(baris, "%19[^|]|%14[^\n]", data.nim, data.kode_mk) != 2)
            continue;
        if (krs_sudah_ada(data.nim, data.kode_mk)) continue;

        baru = (KRS *)malloc(sizeof(KRS));
        if (baru == NULL) {
            printf("Memori tidak cukup saat memuat KRS.\n");
            break;
        }
        strcpy(baru->nim, data.nim);
        strcpy(baru->kode_mk, data.kode_mk);
        baru->next = NULL;

        if (headKRS == NULL) headKRS = baru;
        else {
            bantu = headKRS;
            while (bantu->next != NULL) bantu = bantu->next;
            bantu->next = baru;
        }
    }
    fclose(fp);
}


static void bersihkan_buffer(void);

void update_data_mhs(void) {
    char nim[MAKS_NIM];
    Mahasiswa *mhs;
    char nama_baru[MAKS_NAMA], jurusan_baru[MAKS_JURUSAN];

    printf("\n=== UPDATE DATA MAHASISWA ===\n");
    if (headMhs == NULL) {
        printf("Belum ada data mahasiswa.\n");
        return;
    }
    tampil_data_mhs();
    printf("\nMasukkan NIM mahasiswa yang ingin diubah: ");
    baca_teks(nim, sizeof(nim));
    mhs = cari_mhs(nim);
    if (mhs == NULL) {
        printf("Data mahasiswa tidak ditemukan.\n");
        return;
    }

    printf("Nama baru    : ");
    baca_teks(nama_baru, sizeof(nama_baru));
    printf("Jurusan baru : ");
    baca_teks(jurusan_baru, sizeof(jurusan_baru));
    if (nama_baru[0] == '\0' || jurusan_baru[0] == '\0') {
        printf("Nama dan jurusan tidak boleh kosong. Data tidak diubah.\n");
        return;
    }
    strcpy(mhs->nama, nama_baru);
    strcpy(mhs->jurusan, jurusan_baru);
    simpan_data_mhs();
    printf("Data mahasiswa berhasil diperbarui.\n");
}

void update_data_mk(void) {
    char kode[MAKS_KODE];
    Matakuliah *mk;
    char nama_baru[MAKS_NAMA];
    int sks, hasil;

    printf("\n=== UPDATE DATA MATA KULIAH ===\n");
    if (headMK == NULL) {
        printf("Belum ada data mata kuliah.\n");
        return;
    }
    tampil_data_mk();
    printf("\nMasukkan kode mata kuliah yang ingin diubah: ");
    baca_teks(kode, sizeof(kode));
    mk = cari_mk(kode);
    if (mk == NULL) {
        printf("Mata kuliah tidak ditemukan.\n");
        return;
    }

    printf("Nama mata kuliah baru : ");
    baca_teks(nama_baru, sizeof(nama_baru));
    printf("Jumlah SKS baru        : ");
    hasil = scanf("%d", &sks);
    bersihkan_buffer();
    if (hasil != 1 || sks < 1 || sks > 6 || nama_baru[0] == '\0') {
        printf("Nama tidak boleh kosong dan SKS harus 1 sampai 6. Data tidak diubah.\n");
        return;
    }
    strcpy(mk->nama_mk, nama_baru);
    mk->sks = sks;
    simpan_data_mk();
    printf("Data mata kuliah berhasil diperbarui.\n");
}

void update_data_krs(void) {
    char nim_lama[MAKS_NIM], kode_lama[MAKS_KODE];
    char nim_baru[MAKS_NIM], kode_baru[MAKS_KODE];
    KRS *bantu = headKRS;
    Mahasiswa *mhs;
    Matakuliah *mk;
    int total = 0;

    printf("\n=== UPDATE DATA KRS ===\n");
    if (headKRS == NULL) {
        printf("Belum ada data KRS.\n");
        return;
    }
    tampil_data_krs();
    printf("\nNIM lama       : ");
    baca_teks(nim_lama, sizeof(nim_lama));
    printf("Kode MK lama   : ");
    baca_teks(kode_lama, sizeof(kode_lama));

    while (bantu != NULL && !(strcmp(bantu->nim, nim_lama) == 0 &&
                               strcmp(bantu->kode_mk, kode_lama) == 0))
        bantu = bantu->next;
    if (bantu == NULL) {
        printf("Data KRS tidak ditemukan.\n");
        return;
    }

    printf("NIM baru       : ");
    baca_teks(nim_baru, sizeof(nim_baru));
    printf("Kode MK baru   : ");
    baca_teks(kode_baru, sizeof(kode_baru));
    mhs = cari_mhs(nim_baru);
    mk = cari_mk(kode_baru);
    if (mhs == NULL || mk == NULL) {
        printf("NIM mahasiswa atau kode mata kuliah tidak ditemukan.\n");
        return;
    }
    if (strcmp(nim_lama, nim_baru) != 0 || strcmp(kode_lama, kode_baru) != 0) {
        if (krs_sudah_ada(nim_baru, kode_baru)) {
            printf("KRS tersebut sudah terdaftar.\n");
            return;
        }
    }

    {
        KRS *cek = headKRS;
        while (cek != NULL) {
            if (cek != bantu && strcmp(cek->nim, nim_baru) == 0) {
                Matakuliah *mk_lama = cari_mk(cek->kode_mk);
                if (mk_lama != NULL) total += mk_lama->sks;
            }
            cek = cek->next;
        }
    }
    if (total + mk->sks > BATAS_SKS) {
        printf("Update ditolak karena total SKS melebihi batas %d SKS.\n", BATAS_SKS);
        return;
    }

    strcpy(bantu->nim, nim_baru);
    strcpy(bantu->kode_mk, kode_baru);
    simpan_data_krs();
    printf("Data KRS berhasil diperbarui.\n");
}

static void bersihkan_buffer(void) {
    int karakter;
    while ((karakter = getchar()) != '\n' && karakter != EOF) {}
}

static void menu(void) {
    printf("\n========================================\n");
    printf("       SISTEM INFORMASI AKADEMIK\n");
    printf("========================================\n");
    printf("1. Tambah Data Mahasiswa\n");
    printf("2. Tambah Data Mata Kuliah\n");
    printf("3. Tambah Data KRS\n");
    printf("4. Tampilkan Data Mahasiswa\n");
    printf("5. Tampilkan Data Mata Kuliah\n");
    printf("6. Tampilkan Data KRS\n");
    printf("7. Tampilkan Semua Data\n");
    printf("8. Hapus Data Mahasiswa\n");
    printf("9. Hapus Data Mata Kuliah\n");
    printf("10. Hapus Data KRS\n");
    printf("11. Update Data Mahasiswa\n");
    printf("12. Update Data Mata Kuliah\n");
    printf("13. Update Data KRS\n");
    printf("0. Keluar\n");
    printf("----------------------------------------\n");
    printf("Pilih menu: ");
}

void load_semua_data(void) {
    load_data_mhs();
    load_data_mk();
    load_data_krs();
}

void tampilkan_semua_data(void) {
    tampil_data_mhs();
    tampil_data_mk();
    tampil_data_krs();
}

void bebaskan_semua_data(void) {
    Mahasiswa *mhs;
    Matakuliah *mk;
    KRS *krs;

    while (headMhs != NULL) {
        mhs = headMhs;
        headMhs = headMhs->next;
        free(mhs);
    }

    while (headMK != NULL) {
        mk = headMK;
        headMK = headMK->next;
        free(mk);
    }

    while (headKRS != NULL) {
        krs = headKRS;
        headKRS = headKRS->next;
        free(krs);
    }
}

int main(void) {
    int pilihan;

    load_semua_data();
    printf("Data sebelumnya berhasil dimuat jika file tersedia.\n");

    do {
        menu();
        if (scanf("%d", &pilihan) != 1) {
            printf("Input harus berupa angka.\n");
            bersihkan_buffer();
            pilihan = -1;
            continue;
        }
        bersihkan_buffer();

        switch (pilihan) {
            case 1:
                input_data_mhs();
                break;
            case 2:
                input_data_mk();
                break;
            case 3:
                input_krs();
                break;
            case 4:
                tampil_data_mhs();
                break;
            case 5:
                tampil_data_mk();
                break;
            case 6:
                tampil_data_krs();
                break;
            case 7:
                tampilkan_semua_data();
                break;
            case 8:
                hapus_data_mhs();
                break;
            case 9:
                hapus_data_mk();
                break;
            case 10:
                hapus_data_krs();
                break;
            case 11:
                update_data_mhs();
                break;
            case 12:
                update_data_mk();
                break;
            case 13:
                update_data_krs();
                break;
            case 0:
                printf("Program selesai. Data tetap tersimpan.\n");
                break;
            default:
                printf("Pilihan tidak tersedia.\n");
        }
    } while (pilihan != 0);

    bebaskan_semua_data();
    return 0;
}
