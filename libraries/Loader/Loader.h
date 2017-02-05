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
		double getQty();
	private:
		char state[5];
		long timeStart;
		Motor *motor;
		Timer *timer;
		Tank *tank;
		double qtyLoaded, kgs;
};





#endif /* LIBRARIES_LOADER_LOADER_H_ */
