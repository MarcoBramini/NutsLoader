/*
 * Timer.h
 *
 *  Created on: 04 feb 2017
 *      Author: brami
 */

#ifndef LIBRARIES_TIMER_TIMER_H_
#define LIBRARIES_TIMER_TIMER_H_

#include "Arduino.h"

class Timer{
	public:
		Timer();
		void start();
		void stop();
		void pause();
		void resume();
		long getTimeElapsed();
	private:
		long timeStart, timeNow;
		int minutes, seconds;

};



#endif /* LIBRARIES_TIMER_TIMER_H_ */
