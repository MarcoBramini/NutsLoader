#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "Arduino.h"

class Button{
    public:
        Button(int pin);
        boolean isPressed();
    private:
        int pin;
        int val;
        int oldVal;
};

#endif // BUTTON_H_INCLUDED
