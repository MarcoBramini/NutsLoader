/*
 * tank.h
 *
 *  Created on: 03 feb 2017
 *      Author: brami
 */

#ifndef LIBRARIES_TANK_TANK_H_
#define LIBRARIES_TANK_TANK_H_

#include "Arduino.h"
#include "Filter.h"
#include "LiquidCrystal_I2C.h"

class Tank{
	public:
		Tank(Filter *filter, UltrasonicSensor *sensor, int min, int max, LiquidCrystal_I2C *display);
		int getLevel();
		void setLevel(int level);
		void updateLevel();
		void setMin(int min);
		void setMax(int max);
		int getMin();
		int getMax();
	private:
		double level, min, max, range;
		UltrasonicSensor *sensor;
		Filter *filter;
		LiquidCrystal_I2C *display;
};



#endif /* LIBRARIES_TANK_TANK_H_ */
