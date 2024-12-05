#include "recipe.h"
#include <iostream>
using namespace std;

int main() {
    auto [vec1, vec2] = createRecipeObjects();

    // Measure and print times for Merge Sort

    long long mergeSortTime = measureMergeSort(vec1);
    cout << "Merge Sort Time: " << mergeSortTime << " ms\n";

    long long heapSortTime = measureHeapSort(vec1); // Measure and print times for Heap Sort

    cout << "Heap Sort Time: " << heapSortTime << " ms\n";

    displayPercentageDifference(mergeSortTime, heapSortTime);
    vector<int> numbersVec;
    promptUser(getSortedVector(vec1), vec2); // Display percentage difference

    return 0;
}