/*
 * UltrasonicSensor.h
 *
 *  Created on: 03 feb 2017
 *      Author: brami
 */

#ifndef LIBRARIES_ULTRASONICSENSOR_ULTRASONICSENSOR_H_
#define LIBRARIES_ULTRASONICSENSOR_ULTRASONICSENSOR_H_

#include "Arduino.h"

class UltrasonicSensor{
	public:
		UltrasonicSensor(int trig, int echo);
		void trigger();
		int receiveEcho();
		int getNormalizedValue(long echoTime);
	private:
		int trig, echo;
};




#endif /* LIBRARIES_ULTRASONICSENSOR_ULTRASONICSENSOR_H_ */
