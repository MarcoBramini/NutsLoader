/*
 * Timer.h
 *
 *  Created on: 04 feb 2017
 *      Author: brami
 */

#ifndef LIBRARIES_TIMER_TIMER_H_
#define LIBRARIES_TIMER_TIMER_H_

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"

class Timer{
	public:
		Timer();
		void start();
		void stop();
		void pause();
		void normalize();
		void refresh();
		void printDisplay(LiquidCrystal_I2C *display);
		long getTimeStart();
		void setTimeStart(long timeStart);
		long getTimeElapsed();
		void setTimeElapsed(long timeElapsed);
		String getMinutes();
		void setMinutes(int minutes);
		String getSeconds();
		void setSeconds(int seconds);
		boolean isActive();
		void setActive(boolean active);
		boolean isPaused();
		void setPaused(boolean paused);
	private:
		long timeStart, timeElapsed;
		String minutes, seconds;
		boolean active, paused;
};



#endif /* LIBRARIES_TIMER_TIMER_H_ */
