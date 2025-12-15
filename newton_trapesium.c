#include <stdio.h>
#include <math.h>

/* MENU FUNGSI */
int menu;

/* FUNGSI f(x) */
double f(double x)
{
    switch (menu)
    {
    case 1:
        return exp(5 * x); // e^(5x)
    case 2:
        return sqrt(x * x + 1); // sqrt(x^2 + 1)
    case 3:
        return sqrt(x * x - 3); // sqrt(x^2 - 3)
    case 4:
        return pow(5, x); // 5^x
    case 5:
        return log(x) / x; // ln(x)/x
    default:
        return NAN;
    }
}

int main()
{
    double a, b, h, x, integral = 0, eksak;
    int n;

    printf("=====================================\n");
    printf(" METODE TRAPESIUM (NEWTON COTES)\n");
    printf("=====================================\n");

    printf("Pilih Fungsi:\n");
    printf("1. e^(5x)\n");
    printf("2. sqrt(x^2 + 1)\n");
    printf("3. sqrt(x^2 - 3)\n");
    printf("4. 5^x\n");
    printf("5. ln(x)/x\n");
    printf("Pilihan: ");
    scanf("%d", &menu);

    printf("\nBatas bawah a: ");
    scanf("%lf", &a);
    printf("Batas atas b: ");
    scanf("%lf", &b);
    printf("Masukkan h: ");
    scanf("%lf", &h);

    n = (int)((b - a) / h);

    printf("\nTABEL PERHITUNGAN\n");
    printf("---------------------------------\n");
    printf("| i |   x     |   f(x)          |\n");
    printf("---------------------------------\n");

    for (int i = 0; i <= n; i++)
    {
        x = a + i * h;
        double y = f(x);

        if (isnan(y))
        {
            printf("ERROR: Domain fungsi tidak valid!\n");
            return 1;
        }

        printf("| %d | %.4f | %.6f |\n", i, x, y);

        if (i == 0 || i == n)
            integral += y;
        else
            integral += 2 * y;
    }

    integral *= (h / 2);

    printf("---------------------------------\n");
    printf("\nHasil Aproksimasi = %.6f\n", integral);

    printf("Nilai Eksak: ");
    scanf("%lf", &eksak);

    printf("Galat = %.6f\n", fabs(integral - eksak));

    return 0;
}
