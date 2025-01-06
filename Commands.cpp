#include <Arduino.h>
#include "OrderQueue.h"
#include "Recipes.h"
#include "DispenserMovement.h"
#include "OrderFulfillment.h"
#include "DispenserRecipe.h"
#include "Logger.h"

// Таблица команд
struct Command {
    char symbol;               // Символ команды
    void (*handler)();         // Указатель на функцию-обработчик
};


// Прототипы функций-обработчиков
void Commands_HandleAdd1();
void Commands_HandleAdd2();
void Commands_HandleAdd3();
void Commands_HandleAdd4();
void Commands_HandleClear();
void Commands_HandleStart();
void Commands_HandleBreak();
void Commands_HandleReset();
void Commands_HandleList();
void Commands_HandleQueue();
void Commands_HandleHelp();

// Вспомогательные функции
void PrintQueueItem(int index, const char* recipeName);

constexpr Command commandTable[] = {
    {'1', Commands_HandleAdd1},
    {'2', Commands_HandleAdd2},
    {'3', Commands_HandleAdd3},
    {'4', Commands_HandleAdd4},
    {'C', Commands_HandleClear},
    {'S', Commands_HandleStart},
    {'B', Commands_HandleBreak},
    {'R', Commands_HandleReset},
    {'L', Commands_HandleList},
    {'Q', Commands_HandleQueue},
    {'H', Commands_HandleHelp}
};

constexpr int commandTableSize = sizeof(commandTable) / sizeof(Command);

void Commands_Process(const char* cmd) {
    LOG(LOG_LEVEL_DEBUG, "Received command: %s", cmd);

    if (strlen(cmd) == 0) {
        LOG(LOG_LEVEL_ERROR, "Invalid Command: Empty input");
        return;
    }

    char symbol = cmd[0];
    for (int i = 0; i < commandTableSize; i++) {
        if (commandTable[i].symbol == symbol) {
            LOG(LOG_LEVEL_INFO, "Processing command: %c", symbol);
            commandTable[i].handler();
            return;
        }
    }

    LOG(LOG_LEVEL_ERROR, "Invalid Command: Unknown symbol");
}

// Реализация функций-обработчиков

void Commands_HandleAdd1() {
    LOG(LOG_LEVEL_DEBUG, "Adding recipe ID: 0 (Sparkling Water)");
    if (orderQueue_AddDrink(0)) {
        LOG(LOG_LEVEL_DEBUG, "Added: Sparkling Water");
    } else {
        LOG(LOG_LEVEL_DEBUG, "Queue Full");
    }
}

void Commands_HandleAdd2() {
    LOG(LOG_LEVEL_DEBUG, "Adding recipe ID: 1 (Mint Syrup)");
    if (orderQueue_AddDrink(1)) {
        LOG(LOG_LEVEL_DEBUG, "Added: Mint Syrup");
    } else {
        LOG(LOG_LEVEL_DEBUG, "Queue Full");
    }
}

void Commands_HandleAdd3() {
    LOG(LOG_LEVEL_DEBUG, "Adding recipe ID: 2 (Orange Juice)");
    if (orderQueue_AddDrink(2)) {
        LOG(LOG_LEVEL_DEBUG, "Added: Orange Juice");
    } else {
        LOG(LOG_LEVEL_DEBUG, "Queue Full");
    }
}

void Commands_HandleAdd4() {
    LOG(LOG_LEVEL_DEBUG, "Adding recipe ID: 3 (Triple Mix)");
    if (orderQueue_AddDrink(3)) {
        LOG(LOG_LEVEL_DEBUG, "Added: Triple Mix");
    } else {
        LOG(LOG_LEVEL_DEBUG, "Queue Full");
    }
}

void Commands_HandleClear() {
    LOG(LOG_LEVEL_DEBUG, "Clearing queue");
    orderQueue_Clear();
    LOG(LOG_LEVEL_INFO, "Queue Cleared");
}

void Commands_HandleStart() {
    LOG(LOG_LEVEL_INFO, "Starting order processing");
    if (orderQueue_IsEmpty()) {
        LOG(LOG_LEVEL_DEBUG, "Queue is empty, nothing to start.");
        return;
    }
    LOG(LOG_LEVEL_DEBUG, "Queue state before processing:");
    orderQueue_Print();
    LOG(LOG_LEVEL_DEBUG, "Order Started");
	
	byte currentCupNum = 0;
	while (!orderQueue_IsEmpty()){
		int recipeId = orderQueue_GetNext();
		LOG(LOG_LEVEL_INFO, "Drink #%d - %s", currentCupNum + 1, getRecipeNameById(recipeId));
		dispenserMovement_moveToCup(currentCupNum);
		bool result = protectedDoseRecipe_byId(currentCupNum, recipeId);
		currentCupNum++;
	}
	LOG(LOG_LEVEL_INFO, "Order is ready!");
	dispenserMovement_HomePos();
	orderQueue_Restore();
	serve_order();
	orderQueue_Clear();
}

void Commands_HandleBreak() {
    LOG(LOG_LEVEL_INFO, "Breaking current operation and clearing queue");
    orderQueue_Clear();
    LOG(LOG_LEVEL_INFO, "Operation Stopped");
}

void Commands_HandleReset() {
    LOG(LOG_LEVEL_DEBUG, "System resetting...");
}

void Commands_HandleList() {
    LOG(LOG_LEVEL_INFO, "Listing available recipes");
    Serial.println(F("Recipes:\n1: Sparkling Water\n2: Mint Syrup\n3: Orange Juice\n4: Triple Mix\n"));
}

void Commands_HandleQueue() {
    LOG(LOG_LEVEL_DEBUG, "Displaying current queue");
    if (orderQueue_IsEmpty()) {
        LOG(LOG_LEVEL_INFO, "Queue is empty");
        return;
    }

    String result = "Current Queue:\n";
    int count = orderQueue_GetRemainingCount();
    for (int i = 0; i < count; i++) {
        int recipeId = orderQueue_GetRecipeIdAt(i);
        result += String(i + 1) + ": " + getRecipeNameById(recipeId) + "\n";
    }
    LOG(LOG_LEVEL_INFO, result.c_str());
    return;
}

void Commands_HandleHelp() {
    LOG(LOG_LEVEL_INFO, "Displaying help message");
    Serial.println(F("Commands:\n1-4: Add drink by recipe ID.\nC: Clear queue.\nS: Start order processing.\nB: Break operation.\nR: Reset system.\nL: List recipes.\nQ: Show queue.\nH: Show this help.\n"));
}

void PrintQueueItem(int index, const char* recipeName) {
    char tempBuffer[64];
    snprintf(tempBuffer, sizeof(tempBuffer), "%d: %s\n", index + 1, recipeName);
    Serial.print(tempBuffer);
}
