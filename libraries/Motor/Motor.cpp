/*
 * Motor.cpp
 *
 *  Created on: 04 feb 2017
 *      Author: brami
 */


#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int pin){
	this->pin  = pin;
	this->enabled = 0;
}

void Motor::enable(){
	if(this->enabled == 0){
		digitalWrite(this->pin, HIGH);
		this->enabled = 1;
	}
}

void Motor::disable(){
	if(this->enabled == 1){
		digitalWrite(this->pin, LOW);
		this->enabled = 1;
	}
}

boolean Motor::isEnabled(){
	return this->enabled;
}



