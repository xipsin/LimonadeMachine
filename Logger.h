#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

// Уровни логирования
#define LOG_LEVEL_DEBUG 3
#define LOG_LEVEL_INFO  2
#define LOG_LEVEL_WARN  1
#define LOG_LEVEL_ERROR 0

// Текущий уровень логирования
#define CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG

// Включение/отключение логирования
#define ENABLE_LOGGING 1 // Установите 0 для отключения логов

#if ENABLE_LOGGING
#define LOG(level, ...) logMessage(level, __VA_ARGS__)
#else
#define LOG(level, ...)
#endif

void logMessage(int level, const char* format, ...);
void logMessage_P(int level, const __FlashStringHelper* message);

#endif
