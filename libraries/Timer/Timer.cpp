/*
 * Timer.cpp
 *
 *  Created on: 04 feb 2017
 *      Author: brami
 */

#include "Arduino.h"
#include "Timer.h"

Timer::Timer(){
	this->timeNow = 0;
	this->timeStart = 0;
	this->minutes = 0;
	this->seconds = 0;
}


