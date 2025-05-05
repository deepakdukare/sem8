#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
using namespace std;

void fill_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void vector_add_omp(int *a, int *b, int *result, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}

int main() {
    int *arr1, *arr2, *result;
    int size;

    cout << "Enter size of vector: ";
    cin >> size;

    arr1 = new int[size];
    arr2 = new int[size];
    result = new int[size];

    srand(time(0));

    fill_array(arr1, size);
    cout << "Array 1: ";
    print_array(arr1, size);

    fill_array(arr2, size);
    cout << "Array 2: ";
    print_array(arr2, size);

    double start_time = omp_get_wtime();
    vector_add_omp(arr1, arr2, result, size);
    double end_time = omp_get_wtime();

    cout << "Result (OpenMP): ";
    print_array(result, size);
    cout << "Elapsed Time = " << (end_time - start_time) * 1000 << " milliseconds" << endl;

    delete[] arr1;
    delete[] arr2;
    delete[] result;

    return 0;
}
