#ifndef PINS_H
#define PINS_H

void initializeLed()
{
  pinModeFast(13, OUTPUT);
}


void updateLed()
{
  static unsigned long previous = 0;
  static unsigned long current = 0;
  static int state = HIGH; 
  
  current = millis();
  
  if(current - previous > 1000)
  {
    previous = current;
    state = !state;
    digitalWriteFast(13, state);
  }
  
}

#endif
