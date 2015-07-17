#ifndef PINMAP_H
#define PINMAP_H

//used for the print button
#include "Printer.h"

//These are the settings for all of the pins

//analog joystick pins
#define JOYSTICK_1_X A10
#define JOYSTICK_1_Y A11
#define JOYSTICK_2_X A12
#define JOYSTICK_2_Y A13

//pot pins for scaling
#define POT_1 A3
#define POT_2 A2

//set the digital io pins
#define ACTUATOR_UP 24 
#define ACTUATOR_DOWN 23
#define ESTOP 22

//autonmous button pins
#define AUTO_BUTTON 25
#define AUTO_LIGHT 30

//set the speeds
#define NEUTRAL 127
#define MIN 1
#define MAX 255

//define the states of the robot
#define MANUAL 0
#define AUTONOMOUS 1

//blinking led pin
#define LED 13

//initialize all the inputs
void initializePins()
{
  //joystick pins
  pinMode(JOYSTICK_1_Y, INPUT);
  pinMode(JOYSTICK_2_Y, INPUT);
  
  //pot pins
  pinMode(POT_1, INPUT);
  pinMode(POT_2, INPUT);
  
  //set the digital input pins
  pinModeFast(ACTUATOR_UP, INPUT);
  pinModeFast(ACTUATOR_DOWN, INPUT);
  pinModeFast(ESTOP, INPUT);
  pinModeFast(AUTO_BUTTON, INPUT);
  
  pinModeFast(AUTO_LIGHT, OUTPUT);
}

//update the scaling and joysticks
static inline void updateJoysticks()
{ 
  static int RIGHJOY[4] = {511, 511, 511, 511};
  static int LEFTJOY[4] = {511, 511, 511, 511};  
  RIGHJOY[0] = RIGHJOY[1]; 
  RIGHJOY[1] = RIGHJOY[2];
  RIGHJOY[2] = RIGHJOY[3]; 
  LEFTJOY[0] = LEFTJOY[1]; 
  LEFTJOY[1] = LEFTJOY[2]; 
  LEFTJOY[2] = LEFTJOY[3]; 
  LEFTJOY[3] = analogRead(JOYSTICK_1_Y);
  RIGHJOY[3] = analogRead(JOYSTICK_2_Y);
  int leftFilt = ((RIGHJOY[0] + RIGHJOY[1] + RIGHJOY[2]+ RIGHJOY[3])/4);
  int rightFilt = ((LEFTJOY[0] + LEFTJOY[1] + LEFTJOY[2]+ LEFTJOY[3])/4);
  
  Serial.print(rightFilt);
  Serial.print(" ");
  Serial.print(leftFilt);
  Serial.print(" ");
  //get the actual values
  int leftActual = map(leftFilt, 0, 1023, 0, 255);
  int rightActual = map(rightFilt, 0, 1023, 0, 255);
  
  //get the scale value for each of the pots
  int leftScale = map(analogRead(POT_1), 1023, 0, 0, 126);
  int rightScale = map(analogRead(POT_2), 1023, 0, 0, 126);
  
  if(leftActual > 127)
  {
    leftMotorSpeed = NEUTRAL + map(leftActual - NEUTRAL, 0, NEUTRAL, 0, leftScale);
  }
  else if(leftActual < 127)
  {
    leftMotorSpeed = NEUTRAL - map(NEUTRAL - leftActual, 0, NEUTRAL, 0, leftScale);
  }
  
  if(rightActual > 127)
  {
    rightMotorSpeed = NEUTRAL + map(rightActual - NEUTRAL, 0, NEUTRAL, 0, rightScale);
  }
  else if(rightActual < 127)
  {
    rightMotorSpeed = NEUTRAL - map(NEUTRAL - rightActual, 0, NEUTRAL, 0, rightScale);
  }
  
  /*
  if(130 > rightActual && rightActual > 124)
  {
    rightActual = 127;
  }
  
  if(130 > leftActual && leftActual > 124)
  {
    leftActual = 127;
  }
  */
  
  //set the joystick speed
  //leftMotorSpeed = map(analogRead(JOYSTICK_1_Y), 0, 1023, 0, 255);
  //rightMotorSpeed = map(analogRead(JOYSTICK_2_Y), 0, 1023, 0, 255);
}

//update the actuator
static inline void actuatorUpdate()
{
  if(digitalReadFast(ACTUATOR_UP) == LOW)
  {
    actuatorSpeed = 255;
  }
  else if(digitalReadFast(ACTUATOR_DOWN) == LOW)
  {
    actuatorSpeed = 1;
  }
  else
  {
    actuatorSpeed = 127;
  }
}

//update the autonomous button
static inline void autoUpdate()
{
  static boolean pressed = false;
  
  if(digitalReadFast(AUTO_BUTTON) == LOW)
  {
    pressed = true;
  }
  else if(digitalReadFast(AUTO_BUTTON) == HIGH  && pressed)
  {
    if(stateControl == 1)
    {
      stateControl = 2;
      //printerPrint();
      digitalWriteFast(AUTO_LIGHT, HIGH);
    }
    else
    {
      stateControl = 1;
      digitalWriteFast(AUTO_LIGHT, LOW);
    }
    
    pressed = false;
  }
}

//update the blinking led
static inline void ledUpdate()
{
  static unsigned long current = 0;
  static unsigned long previous = 0;
  static int ledState = HIGH;
  
  current = millis();
  
  if(current - previous > 1000)
  {
    previous = current;
    ledState = !ledState;
  }
} 

//update the estop button
static inline void estopUpdate()
{
  //stop the f***ing robot fast
  if(digitalReadFast(ESTOP) == LOW)
  {
    leftMotorSpeed = 127;
    rightMotorSpeed = 127;
    actuatorSpeed = 127;
  }
}

//update all the analog inputs
static void analogUpdate()
{
  updateJoysticks();
}

static void digitalUpdate()
{
  actuatorUpdate();
  autoUpdate();
  ledUpdate();
  estopUpdate();
}

//update the control to the board
void updateControls()
{
  analogUpdate();
  digitalUpdate();
}

#endif
