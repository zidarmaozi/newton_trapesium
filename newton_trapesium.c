#include <stdlib.h>
#include <math.h>

/* --- VARIABEL GLOBAL --- */
double koef_P[50];
int pangkat_P[50];
int jumlah_suku_P = 0;

double koef_Q[50];
int pangkat_Q[50];
int jumlah_suku_Q = 0;

int pilihan_menu = 0;
// 1: P, 2: sqrt(P), 3: P/Q, 4: sqrt(P/Q)
// 5: P/sqrt(Q), 6: sqrt(P)/Q  <-- MENU BARU

/* --- FUNGSI MATEMATIKA DASAR --- */
double hitung_polinomial(double x, double koef[], int pangkat[], int jumlah_suku)
{
    double hasil = 0.0;
    for (int i = 0; i < jumlah_suku; i++)
    {
        hasil = hasil + (koef[i] * pow(x, pangkat[i]));
    }
    return hasil;
}

/* --- FUNGSI UTAMA --- */
double jalankan_fungsi(double x)
{
    double hasil_P = 0.0;
    double hasil_Q = 0.0;
    double nilai_akhir = 0.0;

    // Hitung dulu nilai dasar P(x)
    hasil_P = hitung_polinomial(x, koef_P, pangkat_P, jumlah_suku_P);

    // LOGIKA MENU
    if (pilihan_menu == 1) // P(x)
    {
        nilai_akhir = hasil_P;
    }
    else if (pilihan_menu == 2) // sqrt(P(x))
    {
        if (hasil_P < 0)
            return NAN;
        nilai_akhir = sqrt(hasil_P);
    }
    else if (pilihan_menu == 3) // P(x) / Q(x)
    {
        hasil_Q = hitung_polinomial(x, koef_Q, pangkat_Q, jumlah_suku_Q);
        if (hasil_Q == 0)
            return NAN;
        nilai_akhir = hasil_P / hasil_Q;
    }
    else if (pilihan_menu == 4) // sqrt( P(x) / Q(x) )
    {
        hasil_Q = hitung_polinomial(x, koef_Q, pangkat_Q, jumlah_suku_Q);
        double pecahan = hasil_P / hasil_Q;
        if (hasil_Q == 0 || pecahan < 0)
            return NAN;
        nilai_akhir = sqrt(pecahan);
    }
    // --- TAMBAHAN BARU ---
    else if (pilihan_menu == 5) // P(x) / sqrt(Q(x))
    {
        hasil_Q = hitung_polinomial(x, koef_Q, pangkat_Q, jumlah_suku_Q);
        // Syarat: Q > 0 (karena di dalam akar DAN jadi penyebut)
        if (hasil_Q <= 0)
            return NAN;
        nilai_akhir = hasil_P / sqrt(hasil_Q);
    }
    else if (pilihan_menu == 6) // sqrt(P(x)) / Q(x)
    {
        hasil_Q = hitung_polinomial(x, koef_Q, pangkat_Q, jumlah_suku_Q);
        // Syarat: P >= 0 (akar) dan Q != 0 (penyebut)
        if (hasil_P < 0 || hasil_Q == 0)
            return NAN;
        nilai_akhir = sqrt(hasil_P) / hasil_Q;
    }

    return nilai_akhir;
}

/* --- FUNGSI BANTUAN INPUT --- */
void input_data_polinomial(char nama_poly, double koef[], int pangkat[], int *jumlah)
{
    printf("\n>> Input untuk Polinomial %c(x):\n", nama_poly);
    printf("   Berapa jumlah suku? ");
    scanf("%d", jumlah);

    for (int i = 0; i < *jumlah; i++)
    {
        printf("   Suku ke-%d | Masukkan Koefisien (angka depan): ", i + 1);
        scanf("%lf", &koef[i]);
        printf("   Suku ke-%d | Masukkan Pangkat   (bulat):       ", i + 1);
        scanf("%d", &pangkat[i]);
    }
}

/* --- PROGRAM UTAMA --- */
int main()
{
    double batas_a, batas_b, h, eksak;
    int n;

    printf("==========================================\n");
    printf(" PROGRAM SIMPSON 1/3 FINAL\n");
    printf("==========================================\n\n");

    // 1. PILIH JENIS FUNGSI
    printf("Pilih Jenis Fungsi:\n");
    printf("1. P(x)\n");
    printf("2. sqrt( P(x) )\n");
    printf("3. P(x) / Q(x)\n");
    printf("4. sqrt( P(x) / Q(x) )\n");
    printf("5. P(x) / sqrt( Q(x) )  [BARU]\n");
    printf("6. sqrt( P(x) ) / Q(x)  [BARU]\n");
    printf("Pilihan Anda (1-6): ");
    scanf("%d", &pilihan_menu);

    // 2. INPUT KOEFISIEN
    if (pilihan_menu == 1 || pilihan_menu == 2)
    {
        input_data_polinomial('P', koef_P, pangkat_P, &jumlah_suku_P);
    }
    else if (pilihan_menu >= 3 && pilihan_menu <= 6)
    {
        printf("\n[ATAS / PEMBILANG]");
        input_data_polinomial('P', koef_P, pangkat_P, &jumlah_suku_P);

        printf("\n[BAWAH / PENYEBUT]");
        input_data_polinomial('Q', koef_Q, pangkat_Q, &jumlah_suku_Q);
    }
    else
    {
        printf("Pilihan tidak ada.\n");
        return 0;
    }

    // 3. INPUT BATAS INTEGRAL
    printf("\n--- Input Batas Integral ---\n");
    printf("Masukkan Batas Bawah (a): ");
    scanf("%lf", &batas_a);
    printf("Masukkan Batas Atas  (b): ");
    scanf("%lf", &batas_b);

    // 4. INPUT H DAN VALIDASI N (REVISI BAGIAN LOOP INI)
    // Kita lakukan loop terus menerus sampai user memasukkan h yang menghasilkan n genap
    while (1)
    {
        printf("Masukkan Jarak antar Pias (h): ");
        scanf("%lf", &h);

        // Hitung n di dalam loop agar terupdate setiap kali user input h baru
        // Kita tambah 1e-9 untuk mengatasi floating point error
        n = (int)((batas_b - batas_a) / h + 1e-9);

        // Cek syarat Simpson 1/3: N harus genap dan positif
        if (n > 0 && n % 2 == 0)
        {
            printf("--> OK! Jumlah pias (n) = %d (Genap)\n", n);
            break; // Keluar dari loop karena input sudah benar
        }
        else
        {
            printf("[WARNING] Nilai n = %d (Ganjil atau <=0).\n", n);
            printf("Metode Simpson 1/3 WAJIB n genap.\n");
            printf("Silakan masukkan nilai h yang lain!\n\n");
            // Loop akan mengulang ke "Masukkan Jarak antar Pias (h)"
        }
    }

    // Input Eksak
    printf("\nMasukkan Nilai Eksak (Analitik): ");
    scanf("%lf", &eksak);

    // 5. PROSES TABEL
    printf("\n--- Tabel Evaluasi ---\n");
    printf("-----------------------------------------\n");
    printf("|  i  |   x      |    f(x)    |\n");
    printf("-----------------------------------------\n");

    double sigma_ganjil = 0.0;
    double sigma_genap = 0.0;
    double f_awal = 0.0;
    double f_akhir = 0.0;
    double y, x;

    for (int i = 0; i <= n; i++)
    {
        x = batas_a + (i * h);
        y = jalankan_fungsi(x);

        if (isnan(y))
        {
            printf("| %-3d | %.4f   |   ERROR    |\n", i, x);
            printf("-----------------------------------------\n");
            printf("Gagal: Domain fungsi invalid (Akar negatif / Bagi nol).\n");
            return 1;
        }

        printf("| %-3d | %.4f   | %.4f     |\n", i, x, y);

        if (i == 0)
            f_awal = y;
        else if (i == n)
            f_akhir = y;
        else if (i % 2 != 0)
            sigma_ganjil += y;
        else
            sigma_genap += y;
    }
    printf("-----------------------------------------\n");

    // 6. HITUNG HASIL AKHIR & GALAT
    double integral = (h / 3.0) * (f_awal + f_akhir + (4 * sigma_ganjil) + (2 * sigma_genap));

    printf("\n>>> HASIL AKHIR INTEGRASI <<<\n");
    printf("Nilai Aproksimasi = %.4f\n", integral);

    // Gunakan fabs() untuk float/double, bukan abs()
    printf("\n>>> HASIL GALAT <<<\n");
    printf("Nilai GALAT       = %.4f\n", fabs(integral - eksak));

    return 0;
}