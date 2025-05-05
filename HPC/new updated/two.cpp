#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

#define N 10000  // Adjust size as needed

// Utility: Check if array is sorted
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Parallel Bubble Sort (with even-odd transposition sort logic)
void parallelBubbleSort(vector<int>& arr) {
    for (int i = 0; i < N; i++) {
        int start = i % 2;
#pragma omp parallel for
        for (int j = start; j < N - 1; j += 2) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Merge function for merge sort
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size())
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    while (i < left.size())
        arr[k++] = left[i++];
    while (j < right.size())
        arr[k++] = right[j++];
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        sequentialMergeSort(arr, l, m);
        sequentialMergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int l, int r, int depth = 0) {
    if (l < r) {
        int m = (l + r) / 2;
        if (depth < 4) { // Limit parallel depth
#pragma omp parallel sections
            {
#pragma omp section
                parallelMergeSort(arr, l, m, depth + 1);
#pragma omp section
                parallelMergeSort(arr, m + 1, r, depth + 1);
            }
        } else {
            sequentialMergeSort(arr, l, m);
            sequentialMergeSort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

int main() {
    srand(time(0));
    vector<int> baseArray(N);
    for (int i = 0; i < N; i++)
        baseArray[i] = rand() % 1000;

    vector<int> arr1 = baseArray;
    double start = omp_get_wtime();
    sequentialBubbleSort(arr1);
    double end = omp_get_wtime();
    cout << "Sequential Bubble Sort Time: " << (end - start) * 1000 << " ms\n";
    cout << "Sorted: " << (isSorted(arr1) ? "Yes" : "No") << "\n";

    vector<int> arr2 = baseArray;
    start = omp_get_wtime();
    parallelBubbleSort(arr2);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << (end - start) * 1000 << " ms\n";
    cout << "Sorted: " << (isSorted(arr2) ? "Yes" : "No") << "\n";

    vector<int> arr3 = baseArray;
    start = omp_get_wtime();
    sequentialMergeSort(arr3, 0, N - 1);
    end = omp_get_wtime();
    cout << "Sequential Merge Sort Time: " << (end - start) * 1000 << " ms\n";
    cout << "Sorted: " << (isSorted(arr3) ? "Yes" : "No") << "\n";

    vector<int> arr4 = baseArray;
    start = omp_get_wtime();
    parallelMergeSort(arr4, 0, N - 1);
    end = omp_get_wtime();
    cout << "Parallel Merge Sort Time: " << (end - start) * 1000 << " ms\n";
    cout << "Sorted: " << (isSorted(arr4) ? "Yes" : "No") << "\n";

    return 0;
}
