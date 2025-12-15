#include <stdio.h>
#include <math.h>

/* -----------------------------
   STRUKTUR FUNGSI UMUM
--------------------------------*/
typedef struct
{
    double A;       // konstanta
    int pangkat_x;  // x^n
    int pangkat_ln; // (ln x)^m
    int pakai_exp;  // 0 / 1
    double k;       // e^(k x)
    int pakai_akar; // 0 / 1
    double a, b, c; // akar: ax^2 + bx + c
} Fungsi;

/* -----------------------------
   EVALUASI f(x)
--------------------------------*/
double f(double x, Fungsi F)
{
    double hasil = F.A;

    // x^n
    hasil *= pow(x, F.pangkat_x);

    // (ln x)^m
    if (F.pangkat_ln > 0)
    {
        if (x <= 0)
            return NAN;
        hasil *= pow(log(x), F.pangkat_ln);
    }

    // e^(k x)
    if (F.pakai_exp)
        hasil *= exp(F.k * x);

    // sqrt(ax^2 + bx + c)
    if (F.pakai_akar)
    {
        double dalam = F.a * x * x + F.b * x + F.c;
        if (dalam <= 0)
            return NAN;
        hasil /= sqrt(dalam);
    }

    return hasil;
}

/* -----------------------------
   MAIN PROGRAM
--------------------------------*/
int main()
{
    Fungsi F;
    double a, b, h, x, integral = 0, eksak;
    int n;

    printf("=====================================\n");
    printf(" METODE TRAPESIUM (UMUM)\n");
    printf("=====================================\n");

    printf("Konstanta A: ");
    scanf("%lf", &F.A);

    printf("Pangkat x (x^n): ");
    scanf("%d", &F.pangkat_x);

    printf("Pangkat ln(x): ");
    scanf("%d", &F.pangkat_ln);

    printf("Pakai e^(kx)? (1=ya,0=tidak): ");
    scanf("%d", &F.pakai_exp);
    if (F.pakai_exp)
    {
        printf("Nilai k: ");
        scanf("%lf", &F.k);
    }

    printf("Pakai akar di penyebut? (1=ya,0=tidak): ");
    scanf("%d", &F.pakai_akar);
    if (F.pakai_akar)
    {
        printf("Masukkan a b c untuk sqrt(ax^2+bx+c): ");
        scanf("%lf %lf %lf", &F.a, &F.b, &F.c);
    }

    printf("\nBatas bawah a: ");
    scanf("%lf", &a);
    printf("Batas atas b: ");
    scanf("%lf", &b);
    printf("Masukkan h: ");
    scanf("%lf", &h);

    n = (int)((b - a) / h);

    printf("\nTABEL\n");
    printf("-----------------------------------\n");
    printf("| i |   x     |   f(x)             |\n");
    printf("-----------------------------------\n");

    for (int i = 0; i <= n; i++)
    {
        x = a + i * h;
        double y = f(x, F);

        if (isnan(y))
        {
            printf("ERROR: Domain fungsi tidak valid\n");
            return 1;
        }

        printf("| %d | %.4f | %.6f |\n", i, x, y);

        if (i == 0 || i == n)
            integral += y;
        else
            integral += 2 * y;
    }

    integral *= (h / 2);

    printf("-----------------------------------\n");
    printf("\nHasil Trapesium = %.6f\n", integral);

    printf("Nilai eksak (jika ada): ");
    scanf("%lf", &eksak);

    printf("Galat = %.6f\n", fabs(integral - eksak));

    return 0;
}
