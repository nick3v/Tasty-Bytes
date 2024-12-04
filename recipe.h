#ifndef RECIPE_H
#define RECIPE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

// Define the Recipe struct
struct Recipe {
    int RecipeId;
    string Name;
    string TotalTime;
    string RecipeCategory;
    string RecipeIngredientQuantities;
    string RecipeIngredientParts;
    string AggregatedRating;
    string Calories;
    string RecipeServings;
    string RecipeInstructions;

    // Constructor
    Recipe(int RecipeId, string Name, string TotalTime, string RecipeCategory,
           string RecipeIngredientQuantities, string RecipeIngredientParts,
           string AggregatedRating, string Calories, string RecipeServings,
           string RecipeInstructions);

    // Display the recipe details
    void display() const;
};

// Function declarations
pair<vector<string>, vector<Recipe>> createRecipeObjects();
long long measureMergeSort(vector<string> vec1);
long long measureHeapSort(vector<string> vec1);
void displayPercentageDifference(long long time1, long long time2);

#endif // RECIPE_H