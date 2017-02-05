/*
 * Filter.cpp
 *
 *  Created on: 03 feb 2017
 *      Author: brami
 */

#include "Arduino.h"
#include "Filter.h"

Filter::Filter(UltrasonicSensor sensor){
	this->sensor = sensor;
	this->reads = 0;
	this->delta = 0;
}

void Filter::readNext(){
	this->sensor.trigger();
	this->readings[reads] = this->sensor.receiveEcho();
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
	int min = 38000;
	for(int i = 0; i<20; i++){
		int sub = (this->readings[i])-(this->delta);
		if(sub<min)
			min = sub;
	}
	return min;
}


