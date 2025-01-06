#ifndef CUPMOVEMENT_SERVO_H
#define CUPMOVEMENT_SERVO_H

#define SERVO_CUP_PIN 25

void cupMovementServo_Initialize();
void cupMovementServo_MoveToAngle(int angle);

#endif