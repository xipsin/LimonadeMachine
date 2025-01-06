#include "RecipesTable.h"

// Таблица рецептов: строки — рецепты, столбцы — ингредиенты
const int recipeTable[][ingredientCount] = {
    {50, 0, 0},   // Газированная вода
    {0, 10, 0},   // Мятный сироп
    {0, 0, 40},   // Апельсиновый сок
    {80, 20, 0},  // Лимонад "Мятный"
    {30, 0, 50},  // Лимонад "Заводной апельсин"
    {35, 10, 45}  // Лимонад "Тройной"
};

const char* recipeNames[] = {
    "Sparkling Water",
    "Mint Syrup",
    "Orange Juice",
    "Mint Lemonade",
    "Orange Fizz",
    "Triple Mix"
};

const int recipeCount = sizeof(recipeNames) / sizeof(recipeNames[0]);
