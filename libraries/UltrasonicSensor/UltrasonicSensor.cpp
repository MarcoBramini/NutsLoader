/*
 * UltrasonicSensor.cpp
 *
 *  Created on: 03 feb 2017
 *      Author: brami
 */

#include "Arduino.h"
#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int trig, int echo){
	this->trig = trig;
	pinMode(this->trig, OUTPUT);
	this->echo = echo;
	pinMode(this->echo, INPUT_PULLUP);
}

void UltrasonicSensor::trigger(){
	digitalWrite(this->trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->trig, LOW);
}

int UltrasonicSensor::receiveEcho(){
	long echoTime = pulseIn(this->echo, HIGH);
	return getNormalizedValue(echoTime);
}

int UltrasonicSensor::getNormalizedValue(long echoTime){
	return 0.017*echoTime;
}


