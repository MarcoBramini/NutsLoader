/*
 * Loader.h
 *
 *  Created on: 04 feb 2017
 *      Author: brami
 */

#ifndef LIBRARIES_LOADER_LOADER_H_
#define LIBRARIES_LOADER_LOADER_H_

#include "Motor.h"
#include "Arduino.h"
#include "Timer.h"
#include "Tank.h"
#include "LiquidCrystal_I2C.h"

class Loader{
	public:
		Loader(Motor *motor, Timer *timer, Tank *tank, double kgs);
		void stateRefilling();
		void statePause();
		void stateStop();
		void refill();
		void pause();
		void resume();
		char* getState();
		void print(LiquidCrystal_I2C * display);
		double getQty();
	private:
		char state[5];
		Motor *motor;
		Timer *timer;
		Tank *tank;
		double qtyLoaded, kgs;
};





#endif /* LIBRARIES_LOADER_LOADER_H_ */
