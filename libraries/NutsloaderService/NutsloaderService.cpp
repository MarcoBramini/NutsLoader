#include "NutsloaderService.h"
#include "Arduino.h"

NutsloaderService::NutsloaderService(NewPing* sonar,
                                     TimerSwitch* cochleaSwitch,
                                     uint16_t minLevelCm,
                                     uint16_t maxLevelCm,
                                     uint8_t stopFillLevel,
                                     uint8_t startFillLevel,
                                     unsigned long obstructionTimeout)
    : sonar(sonar),
      cochleaSwitch(cochleaSwitch),
      minLevelCm(minLevelCm),
      maxLevelCm(maxLevelCm),
      stopFillLevel(stopFillLevel),
      startFillLevel(startFillLevel),
      obstructionTimeout(obstructionTimeout) {}

bool NutsloaderService::mustStopFill() const {
  return currentFillLevel >= stopFillLevel;
}

bool NutsloaderService::canStartFill() const {
  return currentFillLevel < startFillLevel;
}

bool NutsloaderService::isCochleaObstructed() const {
  return millis() - lastLevelChangeTimestamp > obstructionTimeout;
}

int16_t NutsloaderService::readLevelFromSonar() {
  uint16_t levelCm = NewPing::convert_cm(sonar->ping_median(20));
  int16_t level =
      (minLevelCm - (double)levelCm) / (minLevelCm - maxLevelCm) * 100;
  return level;
}

// Control loop
void NutsloaderService::loop() {
  if (error) {
    return;
  }

  // Loop cochlea timer switch
  cochleaSwitch->loop();

  // Read level
  previousFillLevel = currentFillLevel;
  currentFillLevel = readLevelFromSonar();

  if (cochleaSwitch->status()) {
    // Check if cochlea must be deactivated due to fill completed
    if (mustStopFill()) {
      Serial.println("Fill completed, stopping cochlea");
      cochleaSwitch->deactivate();
    }

    if (previousFillLevel != currentFillLevel) {
      lastLevelChangeTimestamp = millis();
    }

    // Check if cochlea must be deactivated due to an error (level not rising
    // for a certain period)
    if (isCochleaObstructed()) {
      Serial.println("Obstruction detected, stopping cochlea");
      cochleaSwitch->deactivate();
      error = true;
    }
  }
}

void NutsloaderService::startFill() {
  if (!error && canStartFill()) {
    cochleaSwitch->activate();
    // Init lastLevelChangeTimestamp for obstruction detection
    lastLevelChangeTimestamp = millis();
  }
}

void NutsloaderService::stopFill() {
  cochleaSwitch->deactivate();
}

int16_t NutsloaderService::getLevel() const {
  return currentFillLevel;
}

bool NutsloaderService::checkError() const {
  return error;
}