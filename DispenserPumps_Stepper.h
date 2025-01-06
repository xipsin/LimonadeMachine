#ifndef DISPENSER_PUMPS_STEPPER_H
#define DISPENSER_PUMPS_STEPPER_H

#include <Arduino.h>

// Инициализирует все подключённые насосы.
void stepperPumps_Init();

void stepperPumps_setTargetDoseInML(size_t pumpIndex, float volumeML);

// Выполняет дозирование заданного объёма жидкости в миллилитрах через указанный насос.
// @param pumpIndex Индекс насоса.
// @param volumeML Объём жидкости в миллилитрах.
void stepperPumps_doseInML(size_t pumpIndex, float volumeML);

bool stepperPumps_pumpTick(size_t pumpIndex);

#endif // DISPENSER_PUMPS_STEPPER_H
