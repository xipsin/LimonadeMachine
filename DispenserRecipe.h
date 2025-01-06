#ifndef DISPENSER_RECIPE_H
#define DISPENSER_RECIPE_H

#include <Arduino.h>

/**
 * @brief Dispenses a recipe by its ID.
 * 
 * This function dispenses the specified recipe by iterating through all ingredients
 * and dosing the required volume for each pump. Logs the process and checks for
 * valid recipe IDs.
 * 
 * @param recipeId The ID of the recipe to dispense.
 */
void doseRecipe_byId(size_t recipeId);
bool protectedDoseRecipe_byId(size_t cupId, size_t recipeId);
#endif
