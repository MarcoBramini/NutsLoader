/*
 * Timer.cpp
 *
 *  Created on: 04 feb 2017
 *      Author: brami
 */

#include "Arduino.h"
#include "Timer.h"
#include "LiquidCrystal_I2C.h"

Timer::Timer(){
	this->timeElapsed = 0;
	this->timeStart = 0;
	this->minutes = "";
	this->seconds = "";
	this->active = false;
	this->paused = false;
}

void Timer::start(){
	if(!isActive()){
		setTimeStart(millis());
		setTimeElapsed(0);
		setActive(true);
	}
}

void Timer::stop(){
	if(isActive()){
		setTimeStart(0);
		setTimeElapsed(millis()-getTimeStart());
		setActive(false);
	}
}

void Timer::pause(){
	if(isActive() && !isPaused()){
		setTimeElapsed(millis() - getTimeStart());
		setPaused(true);
	}
	else if(isActive() && isPaused()){
		setTimeStart(millis() -  getTimeElapsed());
		setPaused(false);
	}
}

void Timer::normalize(){
	long time = getTimeElapsed();
	int minutes = (time/60000)%60;
	int seconds = (time/1000)%60;
	setMinutes(minutes);
	setSeconds(seconds);
}

void Timer::refresh(){
	if(isActive() && !isPaused()){
		setTimeElapsed(millis() - getTimeStart());
		normalize();
	}
}

void Timer::printDisplay(LiquidCrystal_I2C *display){
	display->setCursor(2,1);
	if(getMinutes().toInt() < 10){
		display->print("0");
	}
	display->print(getMinutes());
	display->setCursor(4,1);
	display->print(":");
	if(getSeconds().toInt() < 10){
		display->print("0");
	}
	display->print(getSeconds());
}

long Timer::getTimeElapsed(){
	return this->timeElapsed;
}

void Timer::setTimeElapsed(long timeElapsed) {
	this->timeElapsed = timeElapsed;
}

long Timer::getTimeStart(){
	return this->timeStart;
}

void Timer::setTimeStart(long timeStart) {
	this->timeStart = timeStart;
}

String Timer::getMinutes(){
	return String(this->minutes);
}

void Timer::setMinutes(int minutes) {
	this->minutes = minutes;
}

String Timer::getSeconds(){
	return String(this->seconds);
}

void Timer::setSeconds(int seconds) {
	this->seconds = seconds;
}

void Timer::setActive(boolean active){
	this->active = active;
}

boolean Timer::isActive(){
	return this->active;
}

void Timer::setPaused(boolean paused){
	this->paused = paused;
}

boolean Timer::isPaused(){
	return this->paused;
}
