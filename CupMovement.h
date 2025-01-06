// CupMovement.h
#ifndef CUP_MOVEMENT_H
#define CUP_MOVEMENT_H

#include <Arduino.h>

void cupMovement_Init();
void cupMovement_serveCup(size_t cupId);
void cupMovement_HomePos();
void cupMovement_FirstPos();
void cupMovement_SecondPos();
void cupMovement_ThirdPos();
void cupMovement_FourthPos();

#endif