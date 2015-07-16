#ifndef SERVOS_H
#define SERVOS_H

#include <Servo.h>

static Servo leftMotor;
static Servo rightMotor;
static Servo actuator;

static int currentLeftMotorSpeed = 127;
static int currentRightMotorSpeed = 127;
static int currentActuatorSpeed = 127;

void initializeServos()
{
  leftMotor.attach(5);
  rightMotor.attach(6);
  actuator.attach(3);
}

static void updateRamp()
{
  static unsigned long currentMotor = 0;
  static unsigned long previousMotor = 0;
  static unsigned long currentActuator = 0;
  static unsigned long previousActuator = 0;
  
  currentMotor = millis();
  currentActuator = millis();
  
  if(currentMotor - previousMotor > 10)
  {
    previousMotor = currentMotor;
    if(currentLeftMotorSpeed < leftMotorSpeed)
    {
      currentLeftMotorSpeed += 1;
    }
    else if(currentLeftMotorSpeed > leftMotorSpeed)
    {
      currentLeftMotorSpeed -= 1;
    }
    else
    {
      currentLeftMotorSpeed = leftMotorSpeed;
    }
    
    if(currentRightMotorSpeed < rightMotorSpeed)
    {
      currentRightMotorSpeed += 1;
    }
    else if(currentRightMotorSpeed > rightMotorSpeed)
    {
      currentRightMotorSpeed -= 1;
    }
    else
    {
      currentRightMotorSpeed = rightMotorSpeed;
    }
  }

  if(currentActuator - previousActuator > 5)
  {
    previousActuator = currentActuator;
    
    if(currentActuatorSpeed < actuatorSpeed)
    {
      currentActuatorSpeed += 1;
    }
    else if(currentActuatorSpeed > actuatorSpeed)
    {
      currentActuatorSpeed -= 1;
    }
    else
    {
      currentActuatorSpeed = actuatorSpeed;
    }
  }
  
  if(actuatorSpeed == 0 || leftMotorSpeed == 0 || rightMotorSpeed == 0)
  {
    leftMotorSpeed = 127;
    rightMotorSpeed = 127;
    actuatorSpeed = 127;
    //leftMotor.write(90);
    //rightMotor.write(90);
    //actuator.write(90);
    //leftMotor.write();
    //rightMotor.write(0);
    //actuator.write(0);
  }
}

static void updateSpeeds()
{
  leftMotor.write(map(currentLeftMotorSpeed, 1, 255, 1, 180));
  rightMotor.write(map(currentRightMotorSpeed, 1, 255, 1, 180));
  actuator.write(map(currentActuatorSpeed, 1, 255, 1, 180));
}

void updateServos()
{
  updateRamp();
  updateSpeeds();
}

#endif
