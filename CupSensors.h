#ifndef CUP_SENSOR_H
#define CUP_SENSOR_H

#include <Arduino.h>

extern const byte cupCount;

void cupSensor_Init();
void cupSensor_UpdateStates();
bool cupSensor_getCupState_byIndex(byte btnIndex);
bool cupSensor_checkCupState_byIndex(byte btnIndex);
int cupSensor_getCupsState();
void cupSensor_LogStates();


#endif
