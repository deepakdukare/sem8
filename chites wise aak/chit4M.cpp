#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
using namespace std;

void initialize_matrix(int *array, int rows, int cols){
    for(int i = 0 ; i < rows; i++){
        for(int j = 0; j < cols; j++){
            array[i*cols + j] = rand() % 10;
        }
    }
}

void print_matrix(int *array, int rows, int cols){
    for(int i = 0 ; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << array[i*cols + j] << " ";
        }
        cout << endl;
    }
}

void matrix_multiplication_omp(int *a, int *b, int *c, int common, int c_rows, int c_cols){
    #pragma omp parallel for collapse(2)
    for(int i = 0; i < c_rows; i++){
        for(int j = 0; j < c_cols; j++){
            int sum = 0;
            for(int k = 0; k < common; k++){
                sum += a[i*common + k] * b[k*c_cols + j];
            }
            c[i*c_cols + j] = sum;
        }
    }
}

int main(){
    int A_rows, A_cols, B_rows, B_cols, C_rows, C_cols;
    cout << "Dimensions of matrix 1:\n";
    cout << "Rows: ";
    cin >> A_rows;
    cout << "Columns: ";
    cin >> A_cols;

    cout << "Dimensions of matrix 2:\n";
    cout << "Rows: " << A_cols << endl << "Columns: ";
    cin >> B_cols;

    B_rows = A_cols;
    C_rows = A_rows;
    C_cols = B_cols;

    int A_size = A_rows * A_cols;
    int B_size = B_rows * B_cols;
    int C_size = C_rows * C_cols;

    int *A = new int[A_size];
    int *B = new int[B_size];
    int *C = new int[C_size];

    srand(time(0));

    initialize_matrix(A, A_rows, A_cols);
    cout << "Matrix 1:\n";
    print_matrix(A, A_rows, A_cols);

    initialize_matrix(B, B_rows, B_cols);
    cout << "Matrix 2:\n";
    print_matrix(B, B_rows, B_cols);

    double start = omp_get_wtime();
    matrix_multiplication_omp(A, B, C, A_cols, C_rows, C_cols);
    double end = omp_get_wtime();

    cout << "Result (OpenMP):\n";
    print_matrix(C, C_rows, C_cols);
    cout << "Elapsed Time (OpenMP) = " << (end - start) * 1000 << " milliseconds" << endl;

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
