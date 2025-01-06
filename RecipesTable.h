#ifndef RECIPES_TABLE_H
#define RECIPES_TABLE_H

#include "Ingredients.h"

// Таблица рецептов: строки — рецепты, столбцы — ингредиенты
extern const int recipeTable[][ingredientCount];
extern const char* recipeNames[];
extern const int recipeCount;

#endif
