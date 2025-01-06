#ifndef DISPENSERMOVEMENT_SERVO_H
#define DISPENSERMOVEMENT_SERVO_H

#define SERVO_DISPENSER_PIN 26

void dispenserMovementServo_Initialize();
void dispenserMovementServo_MoveToAngle(int angle);

#endif