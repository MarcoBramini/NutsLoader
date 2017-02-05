#include <Arduino.h>
#include <Filter.h>
#include <LiquidCrystal_I2C.h>
#include <Tank.h>
#include <UltrasonicSensor.h>
#include "Loader.h"
#include "Motor.h"
#include "Timer.h"


#define ECHO 3
#define TRIG 2
#define MAX 10
#define MIN 80
#define MOTOR 5
#define KGS 0.16

UltrasonicSensor sensor = UltrasonicSensor(TRIG,ECHO);
LiquidCrystal_I2C display = LiquidCrystal_I2C(0x27, 20, 4);
Filter filter = Filter(&sensor);
Tank tank = Tank(&filter, &sensor, MIN, MAX, &display);
Motor motor = Motor(MOTOR);
Timer timer = Timer();
Loader loader = Loader(&motor, &timer, &tank, KGS);

void setup(){
	display.init();
	display.backlight();
	display.print("   Booting System");
	for(int i = 0; i<20;i++){

		filter.readNext();
		display.setCursor(0, 1);
		display.print("    Read N.");
		display.print(i);
		display.print(": ");
		display.print(filter.getReading(i));
	}
	tank.updateLevel();
	display.setCursor(0,2);
	display.print("   Tank Level:");
	display.print(tank.getLevel());
	display.print("%");
	display.setCursor(0,3);
	display.print("   Refilling: OFF");
	delay(500);
	display.clear();
	display.setCursor(0,0);
	display.print("   Tank Level:");
	display.print(tank.getLevel());
	display.print("%");
	display.setCursor(0,1);
	display.print("T:00:00");
	display.setCursor(0,2);
	display.print("State:");
	display.setCursor(6,2);
	display.print(loader.getState());
	display.setCursor(13,3);
	display.print(loader.getQty());
	motor.disable();
}

void loop(){


}
