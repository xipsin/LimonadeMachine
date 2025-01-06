// Ingredients.h
#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <Arduino.h>

struct Ingredient {
    const char* name;       // Название компонента
    int id;                 // Уникальный ID компонента
    float viscosity;        // Коэффициент вязкости
    uint32_t color;         // Цвет компонента (RGB)
    float density;          // Плотность компонента (г/мл)
    float minTemp;          // Минимальная температура хранения (°C)
    float maxTemp;          // Максимальная температура хранения (°C)
};

const Ingredient ingredients[] = {
    {"Sparkling Water", 1, 1.0, 0x00BFFF, 1.0, 0.0, 25.0},
    {"Mint Syrup", 2, 1.5, 0x008000, 1.2, 0.0, 25.0},
    {"Orange Juice", 3, 1.2, 0xFFA500, 1.1, 0.0, 5.0}
};

const int ingredientCount = sizeof(ingredients) / sizeof(ingredients[0]);

#endif
