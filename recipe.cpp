#include "recipe.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <algorithm>
using namespace std;
using namespace chrono;

// Constructor implementation
Recipe::Recipe(int RecipeId, string Name, string TotalTime, string RecipeCategory,
               string RecipeIngredientQuantities, string RecipeIngredientParts,
               string AggregatedRating, string Calories, string RecipeServings,
               string RecipeInstructions) {
    this->RecipeId = RecipeId;
    this->Name = Name;
    this->TotalTime = TotalTime;
    this->RecipeCategory = RecipeCategory;
    this->RecipeIngredientQuantities = RecipeIngredientQuantities;
    this->RecipeIngredientParts = RecipeIngredientParts;
    this->AggregatedRating = AggregatedRating;
    this->Calories = Calories;
    this->RecipeServings = RecipeServings;
    this->RecipeInstructions = RecipeInstructions;
}

// Display method implementation
void Recipe::display() const {
    cout << "RecipeId: " << RecipeId << "\n";
    cout << "Name: " << Name << "\n";
    cout << "TotalTime: " << TotalTime << "\n";
    cout << "RecipeCategory: " << RecipeCategory << "\n";
    cout << "RecipeIngredientQuantities: " << RecipeIngredientQuantities << "\n";
    cout << "RecipeIngredientParts: " << RecipeIngredientParts << "\n";
    cout << "AggregatedRating: " << AggregatedRating << "\n";
    cout << "Calories: " << Calories << "\n";
    cout << "RecipeServings: " << RecipeServings << "\n";
    cout << "RecipeInstructions: " << RecipeInstructions << "\n";
}

// Implementation of createRecipeObjects
pair<vector<string>, vector<Recipe>> createRecipeObjects() {
    ifstream file("../pipedrecipes.psv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file.\n";
        return {{}, {}};  // Return empty vectors if file can't be opened
    }

    vector<Recipe> recipeObjectList;
    vector<string> recipeNamesId;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> values;
        string value;

        while (getline(ss, value, '|')) {
            values.push_back(value);
        }

        if (values.size() == 10) {
            Recipe recipe(recipeObjectList.size(), values[1], values[2], values[3],
                          values[4], values[5], values[6], values[7],
                          values[8], values[9]);
            recipeNamesId.push_back(values[1] + to_string(recipeObjectList.size()));
            recipeObjectList.push_back(recipe);
        }
    }

    cout << "Recipes Successfully Imported." << endl;
    cout << "Sorting now." << endl;
    return {recipeNamesId, recipeObjectList};
}

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

// Merge Sort implementation
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

// Heap Sort implementation
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