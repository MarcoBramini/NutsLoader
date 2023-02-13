# NutsLoader

An ESP32 iot-based application that enables to control the reservoir of a biomass heating system.
This is designed to work within HomeAssistant and requires the installation of a MQTT server.

The application automatically sends discovery messages and, therefore, automatically configure itself in HomeAssistant.

The required hardware is:
- ESP32
- SR-HC04
- Compatible relay
- Voltage step-down buck converter

The exposed devices are:
- nutsloader_switch: A binary switch that drives the relay, to which the filling cochlea is connected.
- nutsloader_error_indicator: A binary sensor that notify the user that there's been an error (no change in fuel level timeout). In this state every command is denied and requires the restart of the device to go back to normal behavior.
- nutsloader_level_sensor: A sensor which returns the fill level, read by the ultrasonic sensor.

