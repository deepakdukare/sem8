#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>
#include <iomanip>

using namespace std;
using namespace chrono;

int main() {

    srand(time(0));


    int size = 1000000;
    vector<int> vec1(size), vec2(size), result_seq(size), result_par(size);

    for (int i = 0; i < size; ++i) {
        vec1[i] = rand() % 100;
        vec2[i] = rand() % 100;
    }

    auto start_seq = high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        result_seq[i] = vec1[i] + vec2[i];
    }
    auto end_seq = high_resolution_clock::now();
    duration<double> duration_seq = end_seq - start_seq;

    auto start_par = high_resolution_clock::now();
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        result_par[i] = vec1[i] + vec2[i];
    }
    auto end_par = high_resolution_clock::now();
    duration<double> duration_par = end_par - start_par;
    cout << "Time taken for sequential vector addition: " 
         << fixed << setprecision(6) << duration_seq.count() << " seconds" << endl;

    cout << "Time taken for parallel vector addition with OpenMP: " 
         << fixed << setprecision(6) << duration_par.count() << " seconds" << endl;


    int N = 500;

    vector<vector<int>> mat1(N, vector<int>(N)), mat2(N, vector<int>(N)), result_seq_mat(N, vector<int>(N)), result_par_mat(N, vector<int>(N));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            mat1[i][j] = rand() % 10;
            mat2[i][j] = rand() % 10;
        }
    }

    auto start_seq_mat = high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result_seq_mat[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                result_seq_mat[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    auto end_seq_mat = high_resolution_clock::now();
    duration<double> duration_seq_mat = end_seq_mat - start_seq_mat;

    auto start_par_mat = high_resolution_clock::now();
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result_par_mat[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                result_par_mat[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    auto end_par_mat = high_resolution_clock::now();
    duration<double> duration_par_mat = end_par_mat - start_par_mat;

    cout << "Time taken for sequential matrix multiplication: " 
         << fixed << setprecision(6) << duration_seq_mat.count() << " seconds" << endl;

    cout << "Time taken for parallel matrix multiplication with OpenMP: " 
         << fixed << setprecision(6) << duration_par_mat.count() << " seconds" << endl;

    return 0;
}
