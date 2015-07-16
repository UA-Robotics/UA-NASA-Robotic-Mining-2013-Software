#ifndef DEBUG_H
#define DEBUG_H

void initializeDebug()
{
  Serial.begin(9600);
}

void updateDebug()
{
  
  Serial.print(leftMotorSpeed);
  Serial.print(" ");
  Serial.print(rightMotorSpeed);
  Serial.print(" ");
  Serial.print(actuatorSpeed);
  Serial.print(" ");
  Serial.print(angle);
  Serial.print(" ");
  Serial.print(analogRead(ACTUATOR));
  Serial.println();
}

#endif
