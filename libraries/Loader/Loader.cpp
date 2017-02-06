/*
 * Loader.cpp
 *
 *  Created on: 04 feb 2017
 *      Author: brami
 */

#include "Arduino.h"
#include "Loader.h"
#include "Motor.h"
#include "string.h"
#include "Tank.h"
#include "LiquidCrystal_I2C.h"

Loader::Loader(Motor *motor, Timer *timer, Tank *tank, double kgs){
	this->motor = motor;
	strcpy(this->state, "STOP");
	this->timer = timer;
	this->tank = tank;
	this->qtyLoaded = 0;
	this->kgs = kgs;
}

void Loader::stateRefilling(){
	strcpy(this->state, "FILL");
}

void Loader::statePause(){
	strcpy(this->state, "PAUS");
}

void Loader::stateStop(){
	strcpy(this->state, "STOP");
}

void Loader::refill(){
	int level = this->tank->getLevel();
	if(strcmp(this->state, "STOP ") && level<20){
		stateRefilling();
		this->motor->enable();
		this->timer->start();
	}
	if(strcmp(this->state, "FILL ") && level>95){
		stateStop();
		this->motor->disable();
		this->timer->stop();
	}
}

void Loader::pause(){
	statePause();
	this->motor->disable();
	this->timer->pause();
}

void Loader::resume(){
	if(strcmp(this->state, "PAUS") && this->tank->getLevel()<95){
	stateRefilling();
	this->motor->enable();
	this->timer->pause();
	}
}

char* Loader::getState(){
	return this->state;
}

void Loader::print(LiquidCrystal_I2C *display){
	display->setCursor(6,2);
	display->print(getState());
	display->setCursor(9,1);
	display->print(getQty());
	display->print("kg");
}

double Loader::getQty(){
	this->qtyLoaded = (this->kgs)*((this->timer->getTimeElapsed()/1000));
	return this->qtyLoaded;
}

