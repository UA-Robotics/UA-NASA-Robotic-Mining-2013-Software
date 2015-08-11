//Motor control board
#include <EasyTransfer.h>
#include <Servo.h>
#include <digitalWriteFast.h>

#include "CommStructs.h"
#include "Servos.h"
#include "Pins.h"

void setup()
{
    initializeCommunication();
    initializeServos();
}

void loop()
{
    updateCommunication();
    updateServos();
    updateLed();
}
