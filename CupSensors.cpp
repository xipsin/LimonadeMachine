#include "CupSensors.h"
#include "Logger.h"



struct CupSensor {
    uint8_t pin;   // Пин датчика
    bool state;    // Состояние датчика
};

CupSensor sensors[] = {
    {2, false}, // Датчик 1 на пине 2
    {3, false}, // Датчик 2 на пине 3
    {4, false}, // Датчик 3 на пине 4
    {5, false}  // Датчик 4 на пине 5
};

const byte cupCount = sizeof(sensors) / sizeof(sensors[0]);



void cupSensor_Init() {
    for (byte i = 0; i < cupCount; i++) {
        pinMode(sensors[i].pin, INPUT);
        sensors[i].state = false; // Изначально считаем, что стаканчиков нет
    }
}

void cupSensor_UpdateStates() {
    for (byte i = 0; i < cupCount; i++) {
        sensors[i].state = digitalRead(sensors[i].pin);
    }
}

bool cupSensor_getCupState_byIndex(byte btnIndex){
	if (btnIndex > cupCount){
		LOG(LOG_LEVEL_ERROR, "Wrong button index");
		return 0;
	}
	return sensors[btnIndex].state;
}

bool cupSensor_checkCupState_byIndex(byte btnIndex){
	if (btnIndex > cupCount){
		LOG(LOG_LEVEL_ERROR, "Wrong button index");
		return 0;
	}
	sensors[btnIndex].state = digitalRead(sensors[btnIndex].pin);
	return sensors[btnIndex].state;
}


int cupSensor_getCupsState(){
	int result = 0;
	for (byte i = 0; i < cupCount; i++){
		result = result << 1;
		result += sensors[i].state;
	}
	return result;
}


void cupSensor_LogStates() {
    for (byte i = 0; i < cupCount; i++) {
        logMessage(LOG_LEVEL_DEBUG, "Sensor on pin %d: %s",
                   sensors[i].pin, sensors[i].state ? "Cup present" : "No cup");
    }
}
