// OrderQueue.cpp
#include "OrderQueue.h"
#include <Arduino.h>
#include "Logger.h"


// Очередь заказа
struct OrderQueue {
    int queue[MAX_ORDER_SIZE]; // Массив для хранения ID рецептов
    int front;                 // Указатель на первый элемент
    int rear;                  // Указатель на последний элемент
};

OrderQueue queue;

void orderQueue_Init() {
    LOG(LOG_LEVEL_INFO, "Initializing queue");
    queue.front = 0;
    queue.rear = 0;
}

void orderQueue_Restore(){
	queue.front = 0;
	LOG(LOG_LEVEL_DEBUG, "Queue was restored!");
}

void orderQueue_Clear() {
    LOG(LOG_LEVEL_INFO, "Clearing queue");
    queue.front = 0;
    queue.rear = 0;
}

int orderQueue_GetRemainingCount() {
    int count = queue.rear - queue.front;
    LOG(LOG_LEVEL_DEBUG, "Remaining count: %d", count);
    return count;
}

int orderQueue_PeekNext() {
    if (orderQueue_IsEmpty()) {
        LOG(LOG_LEVEL_WARN, "Peek failed: Queue is empty");
        return -1;
    }
    LOG(LOG_LEVEL_DEBUG, "Peeking next recipe ID: %d", queue.queue[queue.front]);
    return queue.queue[queue.front];
}

int orderQueue_GetNext() {
    if (orderQueue_IsEmpty()) {
        LOG(LOG_LEVEL_WARN, "GetNext failed: Queue is empty");
        return -1;
    }
    int recipeId = queue.queue[queue.front];
    LOG(LOG_LEVEL_INFO, "Getting next recipe ID: %d", recipeId);
    queue.front++;
    return recipeId;
}

bool orderQueue_AddDrink(int recipeId) {
    if (orderQueue_IsFull()) {
        LOG(LOG_LEVEL_WARN, "AddDrink failed: Queue is full");
        return false;
    }
    if (recipeId < 0 || recipeId >= recipeCount) {
        LOG(LOG_LEVEL_ERROR, "AddDrink failed: Invalid recipe ID %d", recipeId);
        return false;
    }
    queue.queue[queue.rear] = recipeId;
    LOG(LOG_LEVEL_INFO, "Added recipe ID: %d at position %d", recipeId, queue.rear);
    queue.rear++;
    return true;
}

bool orderQueue_IsEmpty() {
    bool isEmpty = queue.front == queue.rear;
    LOG(LOG_LEVEL_DEBUG, "Queue is %s", isEmpty ? "empty" : "not empty");
    return isEmpty;
}

bool orderQueue_IsFull() {
    bool isFull = queue.rear >= MAX_ORDER_SIZE;
    LOG(LOG_LEVEL_DEBUG, "Queue is %s", isFull ? "full" : "not full");
    return isFull;
}

void orderQueue_Print() {
    LOG(LOG_LEVEL_DEBUG, "Printing queue state");
    Serial.println("Текущая очередь заказов:");
    for (int i = queue.front; i < queue.rear; i++) {
        Serial.print(" - Рецепт ID: ");
        Serial.println(queue.queue[i]);
    }
}

int orderQueue_GetRecipeIdAt(int index) {
    if (index < 0 || index >= orderQueue_GetRemainingCount()) {
        logMessage(LOG_LEVEL_ERROR, "Index out of bounds: %d", index);
        return -1; // Указывает на ошибку
    }
    return queue.queue[queue.front + index];
}
