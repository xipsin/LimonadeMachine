//OrderFulfillment.cpp
#include "OrderFulfillment.h"
#include "CupMovement.h"
#include "CupSensors.h"
#include "Logger.h"
#include "OrderQueue.h"
//


void serve_drink(size_t cupId, const char *recipeName){
	LOG(LOG_LEVEL_DEBUG, "Перемещение чаши №%d в зону выдачи..", cupId);
	cupMovement_serveCup(cupId);
	LOG(LOG_LEVEL_DEBUG, "Перемещение чаши №%d в зону выдачи завершено!", cupId);
	LOG(LOG_LEVEL_INFO, "№%d - %s. Пожалуйста, заберите напиток!", cupId, recipeName);
	while (cupSensor_checkCupState_byIndex(cupId));
	LOG(LOG_LEVEL_DEBUG, "Напиток №%d был извлечён!", cupId);
}


void serve_order(){
	LOG(LOG_LEVEL_DEBUG, "Начинается выдача заказа!");
	byte currentCupNum = 0;
	while (!orderQueue_IsEmpty()){
		int recipeId = orderQueue_GetNext(); //getRecipeNameById(recipeId)
		LOG(LOG_LEVEL_INFO, "Drink #%d - %s", currentCupNum + 1, getRecipeNameById(recipeId));
		serve_drink(currentCupNum, getRecipeNameById(recipeId));
		currentCupNum++;
	}
	LOG(LOG_LEVEL_INFO, "Заказ завершён!");
	cupMovement_HomePos();
}








