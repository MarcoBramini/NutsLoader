#ifndef _NUTSLOADER_SERVICE_H_
#define _NUTSLOADER_SERVICE_H_

#include "Arduino.h"
#include "NewPing.h"
#include "TimerSwitch.h"

class NutsloaderService {
public:
    NutsloaderService(NewPing *sonar, TimerSwitch *cochleaSwitch, uint16_t minLevelCm, uint16_t maxLevelCm,
                      uint8_t stopFillLevel, uint8_t startFillLevel, unsigned long obstructionTimeout);

    void loop();

    void startFill();

    void stopFill();

    [[nodiscard]] int16_t getLevel() const;

    [[nodiscard]] bool checkError() const;

private:
    // Ultrasonic sensor attributes
    NewPing *sonar{};
    // Cochlea switch attributes
    TimerSwitch *cochleaSwitch{};
    // Settings
    uint16_t minLevelCm = 100, maxLevelCm = 20;
    uint8_t stopFillLevel = 100, startFillLevel = 75;
    unsigned long obstructionTimeout = 20000;

    // State
    int16_t currentFillLevel{}, previousFillLevel{};
    unsigned long lastLevelChangeTimestamp{};
    bool error{};

    // Methods
    int16_t readLevelFromSonar();

    [[nodiscard]] bool mustStopFill() const;

    [[nodiscard]] bool canStartFill() const;

    [[nodiscard]] bool isCochleaObstructed() const;
};

#endif //_NUTSLOADER_SERVICE_H_
