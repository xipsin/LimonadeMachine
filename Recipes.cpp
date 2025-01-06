#include "Recipes.h"
#include <Arduino.h>

const int* getRecipeById(int recipeId) {
    if (recipeId < 0 || recipeId >= recipeCount) {
        Serial.println("Ошибка: неверный ID рецепта.");
        return nullptr;
    }
    return recipeTable[recipeId];
}

const char* getRecipeNameById(int recipeId) {
    if (recipeId < 0 || recipeId >= recipeCount) {
        return "Unknown Recipe";
    }
    return recipeNames[recipeId];
}
