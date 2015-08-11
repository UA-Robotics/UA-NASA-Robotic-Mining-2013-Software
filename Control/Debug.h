#ifndef DEBUG_H
#define DEBUG_H

#include "PinMap.h"

void initializeDebug()
{
    Serial.begin(9600);
}

//This will take care of outputing all debug output
void updateDebug()
{
    Serial.print(leftMotorSpeed);
    Serial.print(" ");
    Serial.print(rightMotorSpeed);
    Serial.print(" ");
    Serial.print(actuatorSpeed);
    Serial.print(" ");
    Serial.print(stateControl);
    Serial.println();
}

#endif
