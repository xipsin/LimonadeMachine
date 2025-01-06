#include "CupMovement.h"
#include "CupMovement_Servo.h"
#include "Logger.h"


// Константы для углов перемещения
#define HOME_POSITION 			0
#define FIRST_CUP_POSITION 		30
#define SECOND_CUP_POSITION 	60
#define THIRD_CUP_POSITION 		90
#define FOURTH_CUP_POSITION 	120



const byte cupPositions[] = {
	FIRST_CUP_POSITION,
	SECOND_CUP_POSITION,
	THIRD_CUP_POSITION,
	FOURTH_CUP_POSITION
};
constexpr size_t cupCount = sizeof(cupPositions) / sizeof(cupPositions[0]);



void cupMovement_Init() {
    cupMovementServo_Initialize();
    logMessage(LOG_LEVEL_INFO, "Высокоуровневая часть узла перемещения стаканчиков инициализирована.");
}




#define CUPMOVEMENT_MOVE_TIMEOUT 800
void cupMovement_serveCup(size_t cupId){
	if (cupId >= cupCount){
		LOG(LOG_LEVEL_ERROR, "Invalid cup ID: %zu. Maximum ID is %zu.", cupId, cupCount - 1);
		return;
	}
	LOG(LOG_LEVEL_DEBUG, "Перемещение чаши №%d в зону выдачи..", cupId);
	cupMovementServo_MoveToAngle(cupPositions[cupId]);
	delay(CUPMOVEMENT_MOVE_TIMEOUT);
	LOG(LOG_LEVEL_DEBUG, "Перемещение чаши №%d в зону выдачи завершено!", cupId);
}




void cupMovement_HomePos() {
    logMessage(LOG_LEVEL_DEBUG, "Высокоуровневая команда: переход в домашнюю позицию.");
    cupMovementServo_MoveToAngle(HOME_POSITION);
}

void cupMovement_FirstPos() {
    logMessage(LOG_LEVEL_DEBUG, "Высокоуровневая команда: выдача первого стакана.");
    cupMovementServo_MoveToAngle(FIRST_CUP_POSITION);
}

void cupMovement_SecondPos() {
    logMessage(LOG_LEVEL_DEBUG, "Высокоуровневая команда: выдача второго стакана.");
    cupMovementServo_MoveToAngle(SECOND_CUP_POSITION);
}

void cupMovement_ThirdPos() {
    logMessage(LOG_LEVEL_DEBUG, "Высокоуровневая команда: выдача третьего стакана.");
    cupMovementServo_MoveToAngle(THIRD_CUP_POSITION);
}

void cupMovement_FourthPos() {
    logMessage(LOG_LEVEL_DEBUG, "Высокоуровневая команда: выдача четвертого стакана.");
    cupMovementServo_MoveToAngle(FOURTH_CUP_POSITION);
}
