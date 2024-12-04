#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <algorithm>
#include "recipe.h"
using namespace std;
using namespace chrono;

// Helper function to extract the number at the end of a string
int extractNumber(const string &s) {
    size_t pos = s.find_last_not_of("0123456789");
    if (pos == string::npos || pos + 1 >= s.size()) return -1;
    return stoi(s.substr(pos + 1));
}

// Helper function to check if a vector is sorted
bool is_sorted(const vector<string> &vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] < vec[i - 1]) return false;
    }
    return true;
}

// Merge Sort implementation for vec1
void merge(vector<string> &vec1, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<string> L(n1);
    vector<string> R(n2);

    for (int i = 0; i < n1; ++i) L[i] = vec1[left + i];
    for (int i = 0; i < n2; ++i) R[i] = vec1[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            vec1[k] = L[i];
            ++i;
        } else {
            vec1[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        vec1[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        vec1[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<string> &vec1, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(vec1, left, mid);
        mergeSort(vec1, mid + 1, right);

        merge(vec1, left, mid, right);
    }
}

// Heap Sort implementation for vec1
void heapify(vector<string> &vec1, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && vec1[left] > vec1[largest]) largest = left;
    if (right < n && vec1[right] > vec1[largest]) largest = right;

    if (largest != i) {
        swap(vec1[i], vec1[largest]);
        heapify(vec1, n, largest);
    }
}

void heapSort(vector<string> &vec1) {
    int n = vec1.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(vec1, n, i);

    for (int i = n - 1; i > 0; --i) {
        swap(vec1[0], vec1[i]);
        heapify(vec1, i, 0);
    }
}

// Measure time for sorting recipes using Merge Sort
long long measureMergeSort(vector<string> vec1) {
    auto start = high_resolution_clock::now();
    mergeSort(vec1, 0, vec1.size() - 1);
    auto end = high_resolution_clock::now();

    // Check if sorted correctly
    if (!is_sorted(vec1)) {
        cerr << "Merge Sort did not sort the vector correctly." << endl;
    }

    return duration_cast<milliseconds>(end - start).count();
}

// Measure time for sorting recipes using Heap Sort
long long measureHeapSort(vector<string> vec1) {
    auto start = high_resolution_clock::now();
    heapSort(vec1);
    auto end = high_resolution_clock::now();

    // Check if sorted correctly
    if (!is_sorted(vec1)) {
        cerr << "Heap Sort did not sort the vector correctly." << endl;
    }

    return duration_cast<milliseconds>(end - start).count();
}

// Calculate and display percentage difference between two times
void displayPercentageDifference(long long time1, long long time2) {
    if (time1 < time2) {
        double percentage = ((time2 - time1) / static_cast<double>(time2)) * 100.0;
        cout << "Merge Sort is " << percentage << "% faster than Heap Sort.\n";
    } else if (time2 < time1) {
        double percentage = ((time1 - time2) / static_cast<double>(time1)) * 100.0;
        cout << "Heap Sort is " << percentage << "% faster than Merge Sort.\n";
    } else {
        cout << "Both sorting algorithms took the same amount of time.\n";
    }
}

// Main function for testing
int main() {
    auto [vec1, vec2] = createRecipeObjects();

    // Measure and print times for Merge Sort
    long long mergeSortTime = measureMergeSort(vec1);
    cout << "Merge Sort Time: " << mergeSortTime << " ms\n";

    // Measure and print times for Heap Sort
    long long heapSortTime = measureHeapSort(vec1);
    cout << "Heap Sort Time: " << heapSortTime << " ms\n";

    // Display percentage difference
    displayPercentageDifference(mergeSortTime, heapSortTime);

    return 0;
}
