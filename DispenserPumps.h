#ifndef DISPENSER_PUMPS_H
#define DISPENSER_PUMPS_H

void dispenserPumps_Init();
bool dispenserPumps_tick(int pumpIndex);
void dispenserPumps_setTargetDoseInML(int pumpIndex, float volumeML);
void dispenserPumps_doseInML(int pumpIndex, float volumeML);


#endif