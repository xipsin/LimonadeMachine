#include <Arduino.h>
#include "BluetoothModule.h"
#include "CupSensors.h"
#include "CupMovement.h"
#include "DispenserMovement.h"
#include "DispenserPumps.h"
#include "OrderQueue.h"
#include "Commands.h"
#include "Logger.h"

void onBluetoothConnect() {
    LOG(LOG_LEVEL_INFO, "Bluetooth connected!");
}

void onBluetoothDisconnect() {
    LOG(LOG_LEVEL_INFO, "Bluetooth disconnected!");
}

void setup() {
    Serial.begin(115200);
    bluetooth_Init("LimonadeMachine");

    // Регистрация колбэков
    bluetooth_OnConnect(onBluetoothConnect);
    bluetooth_OnDisconnect(onBluetoothDisconnect);

	LOG(LOG_LEVEL_INFO, "Initialization of all systems!");
	
	cupSensor_Init();
	cupMovement_Init();
	cupMovement_HomePos();
	dispenserMovement_Init();
	dispenserMovement_HomePos();
	dispenserPumps_Init();
	orderQueue_Init();
	
    LOG(LOG_LEVEL_INFO, "Limonade Machine started!");
}

void loop() {
    bluetooth_CheckConnection();

    if (bluetooth_IsConnected()) {
        if (bluetooth_Available()) {
            char cmd = bluetooth_ReadChar();
			LOG(LOG_LEVEL_DEBUG, "Command %c received via Bluetooth", cmd);
			Commands_Process(&cmd);
        }
    } else {
        LOG(LOG_LEVEL_INFO, "Waiting for Bluetooth connection!");
        delay(500);
    }
}
