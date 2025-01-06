//DispenserRecipe.cpp
#include "DispenserRecipe.h"
#include "DispenserPumps.h"
#include "Ingredients.h"
#include "RecipesTable.h"
#include "Logger.h"
#include "CupSensors.h"







//Unprotected from cup dissapearing
void doseRecipe_byId(size_t recipeId){
	if (recipeId >= recipeCount){
		LOG(LOG_LEVEL_ERROR, "Invalid recipe ID: %zu. Maximum ID is %zu.", recipeId, recipeCount - 1);
		return;
	}
	
	LOG(LOG_LEVEL_INFO, "Dispensering recipe '%s'..", recipeNames[recipeId]);
	
	for (size_t ingredientIndex = 0; ingredientIndex < recipeCount; ingredientIndex++){
		float volumeML = recipeTable[recipeId][ingredientIndex];
		if (volumeML > 0){
			LOG(LOG_LEVEL_INFO, "Dosing %.2f ml of %s...", volumeML, ingredients[ingredientIndex].name);
			dispenserPumps_doseInML(ingredientIndex, volumeML);
			LOG(LOG_LEVEL_INFO, "Dosing of %s completed.", ingredients[ingredientIndex].name);
		}
		
	}
	LOG(LOG_LEVEL_INFO, "Recipe '%s' is ready! Enjoy your drink!", recipeNames[recipeId]);
}






enum DosingState {DOSING_ST, REMOVED_ST, FINISHED_ST, ERROR_ST};
constexpr uint32_t REMOVED_CUP_ERROR_TIMEOUT_MS = 30000;


bool protectedDoseRecipe_byId(size_t cupId, size_t recipeId){
	if (cupId >= cupCount){
		LOG(LOG_LEVEL_ERROR, "Invalid cup ID: %zu. Maximum ID is %zu.", cupId, cupCount - 1);
		return 0;
	}
	if (recipeId >= recipeCount){
		LOG(LOG_LEVEL_ERROR, "Invalid recipe ID: %zu. Maximum ID is %zu.", recipeId, recipeCount - 1);
		return 0;
	}
	
	LOG(LOG_LEVEL_INFO, "Dispensering recipe '%s'..", recipeNames[recipeId]);
	
	bool result = true;
	
	for (size_t ingredientIndex = 0; ingredientIndex < recipeCount; ingredientIndex++){
		float volumeML = recipeTable[recipeId][ingredientIndex];
		if (volumeML > 0){
			LOG(LOG_LEVEL_INFO, "Start dosing %.2f ml of %s...", volumeML, ingredients[ingredientIndex].name);
			dispenserPumps_setTargetDoseInML(ingredientIndex, volumeML);
			
			DosingState state = DOSING_ST;
			
			uint32_t cupRemovedTime = 0;
			while (state != FINISHED_ST){
				switch(state){
					case DOSING_ST:
						if (not cupSensor_checkCupState_byIndex(cupId)){
							LOG(LOG_LEVEL_INFO, "Cup #%d was removed! Pause dosing!");
							cupRemovedTime = millis();
							state = REMOVED_ST;
						}
						if (dispenserPumps_tick(ingredientIndex)){
							LOG(LOG_LEVEL_INFO, "Dosing of %s completed.", ingredients[ingredientIndex].name);
							state = FINISHED_ST;
						}
						break;
					case REMOVED_ST:
						if (cupSensor_checkCupState_byIndex(cupId)){
							LOG(LOG_LEVEL_INFO, "Cup #%d was returned! Continue dosing!");
							state = DOSING_ST;
						}
						if (millis() - cupRemovedTime >= REMOVED_CUP_ERROR_TIMEOUT_MS){
							state = ERROR_ST;
						}
						break;
					case FINISHED_ST:
						break;
					case ERROR_ST:
						LOG(LOG_LEVEL_ERROR, "Error during dosing of %s - Cup #%d was removed for a long time!", ingredients[ingredientIndex].name, cupId);
						dispenserPumps_setTargetDoseInML(ingredientIndex, 0);
						result = false;
						break;
				}
				if (!result){
					LOG(LOG_LEVEL_INFO, "Cancel dosing ingredient!");
					break;
				}
			}
			if (!result){
				LOG(LOG_LEVEL_INFO, "Cancel dosing recipe!");
				return result;
			}
		}
	}
	
	LOG(LOG_LEVEL_INFO, "Recipe '%s' is ready! Enjoy your drink!", recipeNames[recipeId]);
	return result;
}





