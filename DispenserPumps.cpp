#include "DispenserPumps.h"
#include "DispenserPumps_Stepper.h"
#include "Logger.h"

void dispenserPumps_Init(){
	LOG(LOG_LEVEL_DEBUG, "Высокоуровневая инициализация насосов");
	stepperPumps_Init();
}


void dispenserPumps_setTargetDoseInML(int pumpIndex, float volumeML){
	
	stepperPumps_doseInML(pumpIndex, volumeML);
}


bool dispenserPumps_tick(int pumpIndex){
	return stepperPumps_pumpTick(pumpIndex);
}


void dispenserPumps_doseInML(int pumpIndex, float volumeML){
	LOG(LOG_LEVEL_DEBUG, "Высокоуровневая подача %f мл ингредиента №%d", volumeML, pumpIndex);
	dispenserPumps_setTargetDoseInML(pumpIndex, volumeML);
	while (!dispenserPumps_tick(pumpIndex));
	LOG(LOG_LEVEL_DEBUG, "Дозирование завершено!", volumeML, pumpIndex);
}