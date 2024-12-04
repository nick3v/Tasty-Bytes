#include "recipe.h"
#include <iostream>
using namespace std;

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