#ifndef RECIPES_H
#define RECIPES_H

#include "RecipesTable.h"

extern const int recipeTable[][ingredientCount];
extern const char* recipeNames[];
extern const int recipeCount;

const int* getRecipeById(int recipeId);
const char* getRecipeNameById(int recipeId);

#endif
