#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <climits>
#include <chrono>
using namespace std;
using namespace chrono;

int main() {
    const int n = 1000000;
    int* arr = new int[n];

    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000 + 1;
    }

    auto start_seq = high_resolution_clock::now();
    int sum_seq = 0, min_seq = arr[0], max_seq = arr[0];
    for (int i = 0; i < n; i++) {
        sum_seq += arr[i];
        if (arr[i] < min_seq) min_seq = arr[i];
        if (arr[i] > max_seq) max_seq = arr[i];
    }
    double avg_seq = (double)sum_seq / n;
    auto end_seq = high_resolution_clock::now();
    duration<double> duration_seq = end_seq - start_seq;

    cout << "Sequential Results:" << endl;
    cout << "Sum = " << sum_seq << endl;
    cout << "Average = " << avg_seq << endl;
    cout << "Minimum = " << min_seq << endl;
    cout << "Maximum = " << max_seq << endl;
    cout << "Time Taken (Sequential) = " << duration_seq.count() << " seconds" << endl << endl;

    auto start_par = high_resolution_clock::now();
    int sum_par = 0, min_par = INT_MAX, max_par = INT_MIN;
    #pragma omp parallel for reduction(+:sum_par) reduction(min:min_par) reduction(max:max_par)
    for (int i = 0; i < n; i++) {
        sum_par += arr[i];
        if (arr[i] < min_par) min_par = arr[i];
        if (arr[i] > max_par) max_par = arr[i];
    }
    double avg_par = (double)sum_par / n;
    auto end_par = high_resolution_clock::now();
    duration<double> duration_par = end_par - start_par;

    cout << "Parallel Reduction Results:" << endl;
    cout << "Sum = " << sum_par << endl;
    cout << "Average = " << avg_par << endl;
    cout << "Minimum = " << min_par << endl;
    cout << "Maximum = " << max_par << endl;
    cout << "Time Taken (Parallel) = " << duration_par.count() << " seconds" << endl;

    delete[] arr;

    return 0;
}
