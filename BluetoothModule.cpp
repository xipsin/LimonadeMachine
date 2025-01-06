#include "BluetoothModule.h"
#include "Logger.h"

// Глобальные переменные
BluetoothSerial btSerial;
bool isConnected = false;

// Пользовательские колбэки
BluetoothEventCallback onConnectCallback = nullptr;
BluetoothEventCallback onDisconnectCallback = nullptr;

void bluetooth_Init(const char* deviceName) {
    btSerial.begin(deviceName);
    isConnected = false;
    LOG(LOG_LEVEL_INFO, "Bluetooth initialized with name: %s", deviceName);
}

bool bluetooth_IsConnected() {
    bool currentState = btSerial.hasClient();
    if (currentState != isConnected) {
        isConnected = currentState;
        if (isConnected) {
            bluetooth_HandleConnect();
        } else {
            bluetooth_HandleDisconnect();
        }
    }
    return isConnected;
}

char bluetooth_ReadChar() {
    if (btSerial.available() > 0) {
        char ch = btSerial.read();
        LOG(LOG_LEVEL_DEBUG, "Read char: %c", ch);
        return ch;
    }
    return '\0'; // Нет данных
}

int bluetooth_ReadLine(char* buffer, size_t length) {
    size_t bytesRead = 0;
    while (btSerial.available() > 0 && bytesRead < length - 1) {
        char ch = btSerial.read();
        if (ch == '\n') {
            break; // Завершение строки
        }
        buffer[bytesRead++] = ch;
    }
    buffer[bytesRead] = '\0'; // Завершающий нулевой символ
    LOG(LOG_LEVEL_DEBUG, "Read line: %s", buffer);
    return bytesRead;
}

String bluetooth_ReadString() {
    String result = "";
    while (btSerial.available() > 0) {
        char ch = btSerial.read();
        if (ch == '\n') {
            break; // Завершение строки
        }
        result += ch;
    }
    LOG(LOG_LEVEL_DEBUG, "Read string: %s", result.c_str());
    return result;
}

bool bluetooth_Available() {
    return btSerial.available() > 0;
}

void bluetooth_SendMessage(const char* message) {
    if (bluetooth_IsConnected()) {
        btSerial.println(message);
        LOG(LOG_LEVEL_DEBUG, "Sent message: %s", message);
    } else {
        LOG(LOG_LEVEL_ERROR, "Cannot send message: No Bluetooth client connected.");
    }
}

void bluetooth_SendFormattedMessage(const char* format, ...) {
    if (!bluetooth_IsConnected()) {
        LOG(LOG_LEVEL_ERROR, "Cannot send message: No Bluetooth client connected.");
        return;
    }
    
    char buffer[128];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    btSerial.println(buffer);
    LOG(LOG_LEVEL_DEBUG, "Sent formatted message: %s", buffer);
}

void bluetooth_SendString(const String& message) {
    if (bluetooth_IsConnected()) {
        btSerial.println(message);
        LOG(LOG_LEVEL_DEBUG, "Sent String message: %s", message.c_str());
    } else {
        LOG(LOG_LEVEL_ERROR, "Cannot send message: No Bluetooth client connected.");
    }
}

void bluetooth_CheckConnection() {
    bool currentState = btSerial.hasClient();
    if (currentState != isConnected) {
        isConnected = currentState;
        if (isConnected) {
            bluetooth_HandleConnect();
        } else {
            bluetooth_HandleDisconnect();
        }
    }
}

void bluetooth_HandleConnect() {
    LOG(LOG_LEVEL_INFO, "Bluetooth connected");
    if (onConnectCallback) {
        onConnectCallback();
    }
}

void bluetooth_HandleDisconnect() {
    LOG(LOG_LEVEL_INFO, "Bluetooth disconnected");
    if (onDisconnectCallback) {
        onDisconnectCallback();
    }
}

void bluetooth_OnConnect(BluetoothEventCallback callback) {
    onConnectCallback = callback;
}

void bluetooth_OnDisconnect(BluetoothEventCallback callback) {
    onDisconnectCallback = callback;
}
