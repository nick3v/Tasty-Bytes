#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// Define the Recipe struct
struct Recipe {
    string RecipeId;
    string Name;
    string TotalTime;
    string RecipeCategory;
    string RecipeIngredientQuantities;
    string RecipeIngredientParts;
    string AggregatedRating;
    string Calories;
    string RecipeServings;
    string RecipeInstructions;

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

int createRecipeObjects() {
// Define the headings in order
    vector<string> headings = {
            "RecipeId", "Name", "TotalTime", "RecipeCategory", "RecipeIngredientQuantities",
            "RecipeIngredientParts", "AggregatedRating", "Calories", "RecipeServings", "RecipeInstructions"
    };

    // Read the entire CSV file as a single string
    ifstream file("../newrecipes.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file.\n";
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf(); // Read entire file into buffer
    string content = buffer.str(); // Get content as a single string

    file.close(); // Close the file after reading

    // Start processing after the first @
    size_t startPos = content.find('@') + 1; // Move to the character after the first @
    if (startPos == 0) { // No @ found in the file
        cerr << "Error: No delimiter '@' found in the content.\n";
        return 1;
    }

    vector<string> recipeValues(10); // Array to store the 10 values for the first recipe
    size_t endPos;
    int count = 0;
    bool grab = true; // Alternate between grabbing and skipping

    while ((endPos = content.find('@', startPos)) != string::npos) {
        string value = content.substr(startPos, endPos - startPos);

        if (grab && count < 10) {
            // Trim whitespace
            value.erase(0, value.find_first_not_of(" \n\r\t"));
            value.erase(value.find_last_not_of(" \n\r\t") + 1);

            // Store the value in the array
            recipeValues[count] = value;
            count++;
        }

        // Toggle between grabbing and skipping
        grab = !grab;

        // Move to the character after the next @
        startPos = endPos + 1;

        // Stop if we have filled all 10 headings
        if (count >= 10) break;
    }

    // Print the headings and their corresponding values
    for (int i = 0; i < 10; i++) {
        cout << headings[i] << ": " << recipeValues[i] << endl;
    }

}
