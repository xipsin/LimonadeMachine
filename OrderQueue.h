// OrderQueue.h
#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include "Recipes.h"

#define MAX_ORDER_SIZE 4


// Функции для работы с очередью
void orderQueue_Init();
void orderQueue_Restore();
void orderQueue_Clear();
int orderQueue_GetRemainingCount();
int orderQueue_PeekNext();
int orderQueue_GetNext();
bool orderQueue_AddDrink(int recipeId);
bool orderQueue_IsEmpty();
bool orderQueue_IsFull();
void orderQueue_Print();
int orderQueue_GetRecipeIdAt(int index);

#endif
