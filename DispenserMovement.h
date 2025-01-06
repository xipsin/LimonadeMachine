// DispenserMovement.h
#ifndef DISPENSER_MOVEMENT_H
#define DISPENSER_MOVEMENT_H

#include <Arduino.h>

void dispenserMovement_Init();
void dispenserMovement_moveToCup(size_t cupNumber);
void dispenserMovement_HomePos();
void dispenserMovement_FirstPos();
void dispenserMovement_SecondPos();
void dispenserMovement_ThirdPos();
void dispenserMovement_FourthPos();

#endif