#ifndef _TIMER_SWITCH_H_
#define _TIMER_SWITCH_H_

#include "Arduino.h"

class TimerSwitch {
public:
    TimerSwitch(uint switchDigitalPin, long maxActivePeriod);

    bool activate();

    bool deactivate();

    void loop();

    bool status();

    void setStateChangeCallback(void (*onStateChangeCallback)());

private:
    uint switchDigitalPin;
    bool isActive;
    long activatedAt;
    long maxActivePeriod;
    void (*onStateChangeCallback)();
};

#endif //_TIMER_SWITCH_H_
