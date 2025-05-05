#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

void generate_random_array(vector<int>& arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 1000;
    }
}

void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallel_bubble_sort(vector<int>& arr) {
    int n = arr.size();
    #pragma omp parallel for
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = 0; i < k; i++) {
        arr[left + i] = temp[i];
    }
}

void sequentialMergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void parallelMergeSort(vector<int>& arr, int left, int right, int depth = 0) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        if (depth < 3) {
            #pragma omp parallel sections
            {
                #pragma omp section
                parallelMergeSort(arr, left, mid, depth + 1);
                #pragma omp section
                parallelMergeSort(arr, mid + 1, right, depth + 1);
            }
        } else {
            sequentialMergeSort(arr, left, mid);
            sequentialMergeSort(arr, mid + 1, right);
        }
        merge(arr, left, mid, right);
    }
}

int main() {
    int n = 10000;
    vector<int> arr(n);

    generate_random_array(arr, n);

    auto start = high_resolution_clock::now();
    vector<int> arr_bubble = arr;
    bubble_sort(arr_bubble);
    auto end = high_resolution_clock::now();
    duration<double> bubble_sort_time = end - start;
    cout << "Bubble Sort Time: " << bubble_sort_time.count() << " seconds" << endl;

    start = high_resolution_clock::now();
    vector<int> arr_parallel_bubble = arr;
    parallel_bubble_sort(arr_parallel_bubble);
    end = high_resolution_clock::now();
    duration<double> parallel_bubble_sort_time = end - start;
    cout << "Parallel Bubble Sort Time: " << parallel_bubble_sort_time.count() << " seconds" << endl;

    start = high_resolution_clock::now();
    vector<int> arr_merge = arr;
    sequentialMergeSort(arr_merge, 0, n - 1);
    end = high_resolution_clock::now();
    duration<double> merge_sort_time = end - start;
    cout << "Merge Sort Time: " << merge_sort_time.count() << " seconds" << endl;

    start = high_resolution_clock::now();
    vector<int> arr_parallel_merge = arr;
    parallelMergeSort(arr_parallel_merge, 0, n - 1);
    end = high_resolution_clock::now();
    duration<double> parallel_merge_sort_time = end - start;
    cout << "Parallel Merge Sort Time: " << parallel_merge_sort_time.count() << " seconds" << endl;

    return 0;
}
