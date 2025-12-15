#include <iostream>
#include <iomanip>
using namespace std;

#define MAKS 10

void tampilkanMatriks(float matriks[MAKS][MAKS+1], int n) {
    for (int i = 0; i<n; i++) {
        for (int j = 0; j <= n; j++) {
            //mengatur output lebar 8, dan presisi 2
            cout << setw(8) << fixed << setprecision(2) << matriks[i][j];
            if (j == n-1) {     
                cout << " |";
            }
            
        }
        cout << endl;
    }
}

int eliminasigaus( float matriks[MAKS][MAKS + 1], int n){
    for (int k = 0; k < n; k++){
        //memeriksa apakah ada elemen pivot yang bernilai 0
        if ( matriks [k][k] == 0){
            cout <<"ERROR. matriks pivot bernilai 0" << endl;
            return 0;
        }
    
        for (int i = k +1; i < n; i++){
            float faktor = matriks[i][k] / matriks[k][k]; //faktor = elemen_target / elemen_pivot
            for (int j = k; j <= n; j++ ){
                matriks[i][j] = matriks[i][j] - faktor * matriks [k][j]; //baris_baru = baris_lama - faktor * baris_pivot
            }
        }
    }
    return 1;
}

void substitusi( float matriks[MAKS][MAKS + 1], float solusi[MAKS], int n){
    solusi[n-1] = matriks[n-1][n] / matriks[n-1][n-1]; //kZ = b maka Z = b/k 
   for (int i = n - 2; i >= 0; i--) {
        float jumlah = 0;
        for (int j = i + 1; j < n; j++) {
            jumlah += matriks[i][j] * solusi[j];
        }
        solusi[i] = (matriks[i][n] - jumlah) / matriks[i][i];
   }
}

int main() {
    int jumlah_elemen;
    float matriks[MAKS][MAKS +1];
    float solusi[MAKS];

    //input jumlah elemen pda matriks
    cout << "Masukkan jumlah elemen metriks : ";
    cin >> jumlah_elemen;

    //input elemen pada matriks
    cout << "== masukkan elemen matriks ==" << endl;
    for (int i = 0; i < jumlah_elemen; i++){
        for (int j = 0; j <= jumlah_elemen; j++){
            cout << "elemen ke-[" << i << "][" << j << "] : ";
            cin >> matriks[i][j];
        }
        cout << endl;
    }
    cout << endl;

    //menampilkan matriks awal
    cout << "Matriks awal: " << endl;
    tampilkanMatriks(matriks, jumlah_elemen);
    cout << endl;

    //proses eliminasi gauss
    int gauss = eliminasigaus(matriks, jumlah_elemen);

    //menampilkan matriks setelah eliminasi gauss dan solusinya
    if (gauss == 1){
        cout << "Matriks setelah eliminasi gauss: " << endl;
        tampilkanMatriks(matriks, jumlah_elemen);
        cout << endl;

        substitusi(matriks, solusi, jumlah_elemen);
        cout << "Solusi: " << endl;
        for (int i = 0; i < jumlah_elemen; i++){
            cout << "x" << i+1 << " = " << fixed << setprecision(2) << solusi[i] << endl;
        }
    }

    return 0;
}