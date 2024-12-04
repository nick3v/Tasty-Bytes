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
    Recipe(int RecipeId, string Name, string TotalTime, string RecipeCategory, string RecipeIngredientQuantities, string RecipeIngredientParts, string AggregatedRating, string Calories, string RecipeServings, string RecipeInstructions) {
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
    // Display the recipe details
    void display() const {
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
};

pair<vector<string>, vector<Recipe>> createRecipeObjects() {
    int skipCounter = 0;
    ifstream file("../pipedrecipes.psv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file.\n";
        return 1;
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
            recipeNamesId.push_back(values[1]+ to_string(recipeObjectList.size()));
            recipeObjectList.push_back(recipe);
        }
    }


    int id;
    while(true) {
        cout << "Enter a recipe ID (-1 to quit): ";
        cin >> id;
        if(id == -1) break;
        recipeObjectList[id].display();
        cout<<recipeNamesId[id]<<endl;
    }

    return {recipeNamesId, recipeObjectList};
    // do this: auto [vec1, vec2] = createRecipeObjects();
}