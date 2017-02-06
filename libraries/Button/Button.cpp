#include "Arduino.h"
#include "Button.h"

Button::Button(int pin){
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

boolean Button::isPressed(){
    boolean p = false;
    this->val = digitalRead(this->pin);
    if(this->val==HIGH && this->oldVal==LOW){
      p = true;
    }
    this->oldVal = this->val;
    return p;
}
