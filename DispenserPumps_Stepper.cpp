#include <ESP_FlexyStepper.h>
#include "DispenserPumps_Stepper.h"
#include "Logger.h"



// Структура для описания конфигурации каждого шагового насоса
struct StepperPump_Config {
    byte dir_pin;
    byte step_pin;
    ESP_FlexyStepper* pump; // Используем указатель вместо объекта
    bool reversed;
    float ml_to_steps;
    float speed_ml_per_sec;
    float accel_ml_per_sec2;

    StepperPump_Config(byte dir, byte step, bool rev, float ml_steps, float speed, float accel)
        : dir_pin(dir), step_pin(step), pump(new ESP_FlexyStepper()), reversed(rev),
          ml_to_steps(ml_steps), speed_ml_per_sec(speed), accel_ml_per_sec2(accel) {}
};

// Конфигурация насосов
StepperPump_Config pumps[] = {
    {12, 13, false, 4, 1000, 1000},
    {14, 15, false, 4, 1000, 1000},
    {16, 17, false, 4, 1000, 1000}
};

const size_t pumps_count = sizeof(pumps) / sizeof(pumps[0]); // Количество насосов

// Инициализация всех насосов
void stepperPumps_Init() {
    LOG(LOG_LEVEL_INFO, "Инициализация насосов начата");
    for (size_t i = 0; i < pumps_count; i++) {
        LOG(LOG_LEVEL_DEBUG, "Настройка насоса %d: step_pin=%d, dir_pin=%d", i, pumps[i].step_pin, pumps[i].dir_pin);
        pumps[i].pump->connectToPins(pumps[i].step_pin, pumps[i].dir_pin);
        pumps[i].pump->setStepsPerMillimeter(pumps[i].ml_to_steps);
        pumps[i].pump->setSpeedInMillimetersPerSecond(pumps[i].speed_ml_per_sec);
        pumps[i].pump->setAccelerationInMillimetersPerSecondPerSecond(pumps[i].accel_ml_per_sec2);
        LOG(LOG_LEVEL_INFO, "Насос %d настроен", i);
    }
    LOG(LOG_LEVEL_INFO, "Инициализация насосов завершена");
}


void stepperPumps_setTargetDoseInML(size_t pumpIndex, float volumeML){
	if (pumpIndex >= pumps_count) {
        LOG(LOG_LEVEL_ERROR, "Ошибка: индекс насоса %d вне диапазона", pumpIndex);
        return;
    }
	
	if (pumps[pumpIndex].reversed) {
        volumeML = -volumeML;
        LOG(LOG_LEVEL_DEBUG, "Направление дозирования инвертировано: новый объем %.2f мл", volumeML);
    }
	pumps[pumpIndex].pump->setTargetPositionRelativeInMillimeters(volumeML);
}

bool stepperPumps_pumpTick(size_t pumpIndex){
	return pumps[pumpIndex].pump->processMovement();
}

// Дозирование жидкости с помощью указанного насоса
void stepperPumps_doseInML(size_t pumpIndex, float volumeML) {
    if (pumpIndex >= pumps_count) {
        LOG(LOG_LEVEL_ERROR, "Ошибка: индекс насоса %d вне диапазона", pumpIndex);
        return;
    }
	LOG(LOG_LEVEL_DEBUG, "Для насоса №%d используется шаговый двигатель.", pumpIndex);
	
	stepperPumps_setTargetDoseInML(pumpIndex, volumeML);
    unsigned long startTime = millis(); // Время начала операции
	while (not stepperPumps_pumpTick(pumpIndex));
    unsigned long endTime = millis(); // Время окончания операции
    unsigned long duration = endTime - startTime; // Продолжительность операции

    LOG(LOG_LEVEL_INFO, "Дозирование завершено: насос %d, объем %.2f мл, время %.3f сек",
        pumpIndex, volumeML, duration / 1000.0);
}

// Освобождение ресурсов
void stepperPumps_Cleanup() {
    for (size_t i = 0; i < pumps_count; i++) {
        delete pumps[i].pump;
        pumps[i].pump = nullptr;
    }
}
