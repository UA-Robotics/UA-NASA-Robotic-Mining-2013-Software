//Version 1
//Created by Duncan Campbell

#include "EasyTransfer.h"
#include "digitalWriteFast.h"
#include "SoftwareSerial.h"
#include "Adafruit_Thermal.h"

#include "CommStructs.h"
#include "PinMap.h"
#include "Debug.h"
#include "Screen.h" 
#include <avr/pgmspace.h>

void setup()
{
  //initalize the communication
  initializeCommunicaton();
  initializePins();
  //initializeScreen();
  initializeDebug();
}

void loop()
{
  updateControls();
  updateCommunication();
  //updateScreen();
  updateDebug();
}
