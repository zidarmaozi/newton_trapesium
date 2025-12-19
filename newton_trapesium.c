#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double koef_P[50];
int pangkat_P[50];
int jumlah_suku_P = 0;

double koef_Q[50];
int pangkat_Q[50];
int jumlah_suku_Q = 0;

/*---[ Variabel Tambahan untuk Fungsi Non-Polinomial ]---*/
double koef_eksponen = 0.0;   // Untuk e^(koef*x)
double basis_logaritma = 0.0; // Untuk a^x

int pilihan_menu = 0;

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

/* --- FUNGSI UTAMA f(x) --- */
double jalankan_fungsi(double x)
{
    double hasil_P = 0.0;
    double hasil_Q = 0.0;
    double nilai_akhir = 0.0;

    // Hanya hitung P(x) jika diperlukan (untuk menu 1-6)
    if (pilihan_menu >= 1 && pilihan_menu <= 6)
    {
        hasil_P = hitung_polinomial(x, koef_P, pangkat_P, jumlah_suku_P);
    }

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
    // ... (Menu 3 sampai 6 sama seperti, perlu Q(x))
    else if (pilihan_menu >= 3 && pilihan_menu <= 6)
    {
        hasil_Q = hitung_polinomial(x, koef_Q, pangkat_Q, jumlah_suku_Q);

        if (pilihan_menu == 3) // P(x) / Q(x)
        {
            if (hasil_Q == 0)
                return NAN;
            nilai_akhir = hasil_P / hasil_Q;
        }
        else if (pilihan_menu == 4) // sqrt( P(x) / Q(x) )
        {
            double pecahan = hasil_P / hasil_Q;
            if (hasil_Q == 0 || pecahan < 0)
                return NAN;
            nilai_akhir = sqrt(pecahan);
        }
        else if (pilihan_menu == 5) // P(x) / sqrt(Q(x))
        {
            if (hasil_Q <= 0)
                return NAN;
            nilai_akhir = hasil_P / sqrt(hasil_Q);
        }
        else if (pilihan_menu == 6) // sqrt(P(x)) / Q(x)
        {
            if (hasil_P < 0 || hasil_Q == 0)
                return NAN;
            nilai_akhir = sqrt(hasil_P) / hasil_Q;
        }
    }

    // untuk soal no 1
    else if (pilihan_menu == 7) // e^(koef*x). Contoh: e^(5x) -> koef=5
    {
        // Gunakan exp(x) yang setara dengan e^x
        nilai_akhir = exp(koef_eksponen * x);
    }
    else if (pilihan_menu == 8) // basis^x. Contoh: 5^x -> basis=5
    {
        // Gunakan pow(basis, pangkat)
        if (basis_logaritma <= 0 && (x != round(x))) // Mencegah akar basis negatif
            return NAN;

        nilai_akhir = pow(basis_logaritma, x);
    }
    else if (pilihan_menu == 9) // ln(x) / x
    {
        // Syarat ln(x) : x > 0. Syarat /x : x != 0. Jadi x > 0.
        if (x <= 0)
            return NAN;

        // Gunakan log(x) untuk natural logarithm (ln)
        nilai_akhir = log(x) / x;
    }
    // ------------------------------------

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
        printf("   Suku ke-%d | Masukkan Pangkat   (bulat):        ", i + 1);
        scanf("%d", &pangkat[i]);
    }
}

int main()
{
    double batas_a, batas_b, h, eksak;
    int n;

    printf("==========================================\n");
    printf(" PROGRAM NEWTON COTES - KAIDAH TRAPESIUM\n");
    printf("==========================================\n\n");

    /*---[ PILIH JENIS FUNGSI ]---*/
    printf("Pilih Jenis Fungsi f(x):\n");
    printf("-------------------------------------------------\n");
    printf("1. f(x) = P(x)\n");
    printf("2. f(x) = sqrt( P(x) )\n");
    printf("3. f(x) = P(x) / Q(x)\n");
    printf("4. f(x) = sqrt( P(x) / Q(x) )\n");
    printf("5. f(x) = P(x) / sqrt( Q(x) )\n");
    printf("6. f(x) = sqrt( P(x) ) / Q(x)\n");
    printf("7. f(x) = e^(A * x)\n");
    printf("8. f(x) = B^x\n");
    printf("9. f(x) = ln(x) / x\n");
    printf("-------------------------------------------------\n");
    printf("Masukkan Pilihan Anda (1 - 9): ");
    scanf("%d", &pilihan_menu);

    /*---[ Input Data Polinomial ]---*/
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
    else if (pilihan_menu == 7)
    {
        printf("\n[Eksponensial]");
        printf("Masukkan Koefisien A (untuk e^(A*x), cth: 5): ");
        scanf("%lf", &koef_eksponen);
    }
    else if (pilihan_menu == 8)
    {
        printf("\n[Eksponensial Lain]");
        printf("Masukkan Basis B (untuk B^x, cth: 5): ");
        scanf("%lf", &basis_logaritma);
    }
    else if (pilihan_menu == 9)
    {
        printf("\n[Logaritma Natural] Fungsi f(x) = ln(x)/x\n");
    }
    else
    {
        printf("Pilihan tidak ada.\n");
        return 0;
    }

    /*---[ Input Batas Integral ]---*/
    printf("\n--- Input Batas Integral ---\n");
    printf("Masukkan Batas Bawah (a): ");
    scanf("%lf", &batas_a);
    printf("Masukkan Batas Atas  (b): ");
    scanf("%lf", &batas_b);

    /*---[ Input Jarak antar Pias (h) dan Hitung n ]---*/
    while (1)
    {
        printf("Masukkan Jarak antar Pias (h): ");
        scanf("%lf", &h);

        // n = (b-a)/h
        n = (int)((batas_b - batas_a) / h + 1e-9);

        // Kaidah Trapesium hanya perlu n > 0
        if (n > 0)
        {
            printf("-->Hasil jumlah pias (n) = %d\n", n);
            break;
        }
        else
        {
            printf("[Peringatan] Nilai n = %d (<= 0).\n", n);
            printf("Jumlah pias WAJIB positif. Silakan masukkan nilai h yang lain!\n\n");
        }
    }

    /*---[ Input Nilai Eksak ]---*/
    printf("\nMasukkan Nilai Eksak (Analitik): ");
    scanf("%lf", &eksak);

    /*---[ Untuk Menampilkan Tabel Evaluasi ]---*/
    printf("\n--- Tabel Evaluasi ---\n");
    printf("-----------------------------------\n");
    printf("|  i  |   x      |   f(x_i)   |\n");
    printf("-----------------------------------\n");

    double sigma_tengah = 0.0;
    double f_awal = 0.0;
    double f_akhir = 0.0;
    double y, x;

    for (int i = 0; i <= n; i++)
    {
        x = batas_a + (i * h);
        y = jalankan_fungsi(x);

        if (isnan(y))
        {
            printf("| %-3d | %.4f   |  ERROR   |\n", i, x);
            printf("-----------------------------------\n");
            printf("Gagal: Domain fungsi invalid (Akar negatif / Bagi nol / Logaritma negatif) di x = %.4f.\n", x);
            return 1;
        }

        printf("| %-3d | %.4f   | %.4f   |\n", i, x, y);

        if (i == 0)
            f_awal = y; // f(x0)
        else if (i == n)
            f_akhir = y; // f(xn)
        else
            sigma_tengah += y; // Sigma f(xi) untuk i = 1 sampai n-1
    }
    printf("-----------------------------------\n");

    /*---[ HITUNG INTEGRAL DENGAN KAIDAH TRAPESIUM ]---*/
    // Rumus Trapesium: I = (h/2) * [ f(x0) + 2*Sigma(f(xi)) + f(xn) ]
    double integral = (h / 2.0) * (f_awal + f_akhir + (2 * sigma_tengah));

    printf("\n>>> HASIL AKHIR INTEGRASI (Kaidah Trapesium) <<<\n");
    printf("Nilai Aproksimasi = %.6f\n", integral);

    printf("\n>>> HASIL GALAT <<<\n");
    printf("Nilai GALAT         = %.6f\n", fabs(integral - eksak));

    return 0;
}