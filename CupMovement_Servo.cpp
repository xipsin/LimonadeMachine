#include <ESP32Servo.h>
#include "CupMovement_Servo.h"
#include "Logger.h"

Servo servoCup;

void cupMovementServo_Initialize() {
    servoCup.attach(SERVO_CUP_PIN);
    logMessage(LOG_LEVEL_INFO, "Сервопривод для узла перемещения стаканчиков инициализирован.");
}

void cupMovementServo_MoveToAngle(int angle) {
    logMessage(LOG_LEVEL_DEBUG, "Сервопривод: перемещение на угол.");
    servoCup.write(angle);
}