/*
 * Filter.cpp
 *
 *  Created on: 03 feb 2017
 *      Author: brami
 */

#include "Arduino.h"
#include "Filter.h"

Filter::Filter(UltrasonicSensor *sensor){
	this->sensor = sensor;
	this->reads = 0;
	this->delta = 0;
}

void Filter::readNext(){
	this->sensor->trigger();
	this->readings[reads] = this->sensor->receiveEcho();
	this->reads++;
}

void Filter::calculateDelta(){
	int sum = 0;
	for(int i = 0; i<20; i++){
		sum += this->readings[i];
	}
	this->delta = sum/20;
	this->reads = 0;
}

int Filter::filterData(){
	calculateDelta();
	int min = 99;
	int sub = 0;
	int best = 0;
	for(int i = 0; i<20; i++){
		sub = (getReading(i))-(getDelta());
		if(sub<min){
			min = sub;
			best = getReading(i);
		}
	}
	return best;
}

int Filter::getReading(int i){
	return this->readings[i];
}

int Filter::getDelta(){
	return this->delta;
}

