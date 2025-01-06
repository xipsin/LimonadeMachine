#ifndef BLUETOOTH_MODULE_H
#define BLUETOOTH_MODULE_H

#include <Arduino.h>
#include <BluetoothSerial.h>

// Глобальные переменные
extern BluetoothSerial btSerial;
extern bool isConnected;

// Инициализация Bluetooth
void bluetooth_Init(const char* deviceName);

// Проверка подключения
bool bluetooth_IsConnected();

// Чтение одного символа
char bluetooth_ReadChar();

// Чтение строки до символа \n
int bluetooth_ReadLine(char* buffer, size_t length);

// Чтение строки с использованием String
String bluetooth_ReadString();

// Проверка наличия данных
bool bluetooth_Available();

// Отправка данных
void bluetooth_SendString(const String& message);
void bluetooth_SendMessage(const char* message);

// Форматированный вывод
void bluetooth_SendFormattedMessage(const char* format, ...);

// Обработка событий подключения/отключения
void bluetooth_CheckConnection();
void bluetooth_HandleConnect();
void bluetooth_HandleDisconnect();

// Регистрация пользовательских колбэков
typedef void (*BluetoothEventCallback)();
void bluetooth_OnConnect(BluetoothEventCallback callback);
void bluetooth_OnDisconnect(BluetoothEventCallback callback);

#endif
