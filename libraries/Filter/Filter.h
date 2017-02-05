/*
 * Filter.h
 *
 *  Created on: 03 feb 2017
 *      Author: brami
 */

#ifndef LIBRARIES_FILTER_FILTER_H_
#define LIBRARIES_FILTER_FILTER_H_

#include "Arduino.h"
#include "UltrasonicSensor.h"

class Filter{
	public:
		Filter(UltrasonicSensor sensor);
		void readNext();
		int filterData();
		void calculateDelta();
	private:
		UltrasonicSensor sensor;
		int readings[20];
		int reads;
		int delta;
};




#endif /* LIBRARIES_FILTER_FILTER_H_ */
