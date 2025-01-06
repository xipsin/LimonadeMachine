#include "DispenserMovement.h"
#include "DispenserMovement_Servo.h"
#include "Logger.h"


// Константы для углов перемещения
#define HOME_POSITION 			30
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


void dispenserMovement_Init() {
    dispenserMovementServo_Initialize();
    logMessage(LOG_LEVEL_INFO, "Высокоуровневая часть узла перемещения стаканчиков инициализирована.");
}



#define DISPENSER_MOVE_TIMEOUT 800

void dispenserMovement_moveToCup(size_t cupId) {
	if (cupId >= cupCount){
		LOG(LOG_LEVEL_ERROR, "Invalid cup ID: %zu. Maximum ID is %zu.", cupId, cupCount - 1);
		return;
	}
	LOG(LOG_LEVEL_DEBUG, "Перемещение диспенсера к чаше №%d..", cupId);
	dispenserMovementServo_MoveToAngle(cupPositions[cupId]);
	delay(DISPENSER_MOVE_TIMEOUT);
	LOG(LOG_LEVEL_DEBUG, "Перемещение диспенсера к чаше №%d Завершено!", cupId);
}

void dispenserMovement_HomePos() {
    logMessage(LOG_LEVEL_DEBUG, "Высокоуровневая команда: переход в домашнюю позицию.");
    dispenserMovementServo_MoveToAngle(HOME_POSITION);
}

void dispenserMovement_FirstPos() {
    logMessage(LOG_LEVEL_DEBUG, "Высокоуровневая команда: выдача первого стакана.");
    dispenserMovementServo_MoveToAngle(FIRST_CUP_POSITION);
}

void dispenserMovement_SecondPos() {
    logMessage(LOG_LEVEL_DEBUG, "Высокоуровневая команда: выдача второго стакана.");
    dispenserMovementServo_MoveToAngle(SECOND_CUP_POSITION);
}

void dispenserMovement_ThirdPos() {
    logMessage(LOG_LEVEL_DEBUG, "Высокоуровневая команда: выдача третьего стакана.");
    dispenserMovementServo_MoveToAngle(THIRD_CUP_POSITION);
}

void dispenserMovement_FourthPos() {
    logMessage(LOG_LEVEL_DEBUG, "Высокоуровневая команда: выдача четвертого стакана.");
    dispenserMovementServo_MoveToAngle(FOURTH_CUP_POSITION);
}
