/*
 * Motor.h
 *
 *  Created on: 04 feb 2017
 *      Author: brami
 */

#ifndef LIBRARIES_MOTOR_MOTOR_H_
#define LIBRARIES_MOTOR_MOTOR_H_

#include "Arduino.h"

class Motor{
	public:
		Motor(int pin);
		void enable();
		void disable();
		boolean isEnabled();
	private:
		boolean enabled;
		int pin;
};



#endif /* LIBRARIES_MOTOR_MOTOR_H_ */
