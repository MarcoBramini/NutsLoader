#include "TimerSwitch.h"

TimerSwitch::TimerSwitch(uint switchDigitalPin,
                         long maxActivePeriod
) : switchDigitalPin(switchDigitalPin),
    maxActivePeriod(maxActivePeriod),
    isActive(false) {

    pinMode(switchDigitalPin, OUTPUT);
    digitalWrite(switchDigitalPin, LOW);
}

// Activates the switch, if it isn't already
bool TimerSwitch::activate() {
    if (isActive) return false;

    isActive = true;
    digitalWrite(switchDigitalPin, HIGH);
    activatedAt = millis();
    onStateChangeCallback();
    return true;
}

// Deactivates the switch, if it isn't already
bool TimerSwitch::deactivate() {
    if (!isActive) return false;

    isActive = false;
    digitalWrite(switchDigitalPin, LOW);
    onStateChangeCallback();
    return true;
}

// Performs routine checks for the switch
void TimerSwitch::loop() {
    // Disable the switch if it's been activated for a time bigger
    // than the maximum active period.
    long now = millis();
    if (isActive && now - activatedAt >= maxActivePeriod) {
        deactivate();
    }
}

bool TimerSwitch::status() {
    return isActive;
}

void TimerSwitch::setStateChangeCallback(void (*onStateChangeCallback)()) {
    this->onStateChangeCallback = onStateChangeCallback;
}