/*
 * tank.cpp
 *
 *  Created on: 03 feb 2017
 *      Author: brami
 */

#include "Arduino.h"
#include "Tank.h"

Tank::Tank(Filter filter, UltrasonicSensor sensor, int min, int max, LiquidCrystal_I2C *l){
	this->level = 0;
	this->filter = filter;
	this->sensor = sensor;
	this->min = min;
	this->max = max;
	this->range = min - max;
	this->display = l;
}

void Tank::setLevel(int level){
	this->level = level;
}

int Tank::getLevel(){
	return this->level;
}

void Tank::updateLevel(){
	int value = filter.filterData();
	int normVal = min - value ;
	this->level = (normVal/this->range)*100;
}

void Tank::setMax(int max){
	this->max = max;
}

void Tank::setMin(int min){
	this->min = min;
}

int Tank::getMax(){
	return this->max;
}

int Tank::getMin(){
	return this->min;
}

