#pragma once
/**
 * @file mascot_manager.h
 * @brief Mascot state management stub
 */

#include <Arduino.h>

class MascotManager {
public:
    bool isTalking() { return false; }
    uint8_t getMood() { return 0; }
    void setMood(uint8_t mood) {}
    void talk() {}
    void stopTalking() {}
};

extern MascotManager mascot_manager;
