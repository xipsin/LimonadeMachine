#include <ESP32Servo.h>
#include "DispenserMovement_Servo.h"
#include "Logger.h"

Servo servoDispenser;

void dispenserMovementServo_Initialize() {
    servoDispenser.attach(SERVO_DISPENSER_PIN);
    LOG(LOG_LEVEL_INFO, "Сервопривод для узла перемещения диспенсера инициализирован.");
}

void dispenserMovementServo_MoveToAngle(int angle) {
    LOG(LOG_LEVEL_DEBUG, "Сервопривод диспенсера: перемещение на угол %d.", angle);
    servoDispenser.write(angle);
}