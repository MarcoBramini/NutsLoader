################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/Marco/Desktop/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.17/libraries/Wire/src/Wire.cpp 

LINK_OBJ += \
./libraries/Wire/src/Wire.cpp.o 

CPP_DEPS += \
.\libraries\Wire\src\Wire.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/Wire/src/Wire.cpp.o: C:/Users/Marco/Desktop/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.17/libraries/Wire/src/Wire.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Users\Marco\Desktop\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"C:\Users\Marco\Desktop\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.17\cores\arduino" -I"C:\Users\Marco\Desktop\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.17\variants\standard" -I"C:\Users\Marco\Desktop\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.17\libraries\Wire" -I"C:\Users\Marco\Desktop\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.17\libraries\Wire\src" -I"C:\Users\Marco\Desktop\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.17\libraries\Button" -I"C:\Users\Marco\Desktop\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.17\libraries\Filter" -I"C:\Users\Marco\Desktop\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.17\libraries\LiquidCrystal_I2C" -I"C:\Users\Marco\Desktop\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.17\libraries\Tank" -I"C:\Users\Marco\Desktop\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.17\libraries\UltrasonicSensor" -I"C:\Users\Marco\Desktop\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.17\libraries\Loader" -I"C:\Users\Marco\Desktop\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.17\libraries\Motor" -I"C:\Users\Marco\Desktop\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.17\libraries\Timer" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


