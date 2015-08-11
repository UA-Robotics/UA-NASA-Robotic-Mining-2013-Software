//Version 1
//Created by Duncan Campbell and Grant Carroll

#include <EasyTransfer.h>
#include <digitalWriteFast.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "CommStructs.h"
#include "Sensors.h"
#include "Debug.h"
#include "Leds.h"

void setup()
{
    initializeCommunicaton();
    initializeDebug();
    initializeLeds();
    initializeLed();
    initializeSensors();
}


void loop()
{
    updateCommunication();
    updateDebug();
    updateLeds();
    updateLed();
    updateSensors();
}
