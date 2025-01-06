#include "Logger.h"
#include <Arduino.h>
#include <stdarg.h>

void logMessage(int level, const char* format, ...) {
    if (level <= CURRENT_LOG_LEVEL) {
        char buffer[128]; // Размер буфера можно изменить при необходимости
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        Serial.println(buffer);
    }
}

void logMessage_P(int level, const __FlashStringHelper* message) {
    if (level <= CURRENT_LOG_LEVEL) {
        Serial.println(message);
    }
}
