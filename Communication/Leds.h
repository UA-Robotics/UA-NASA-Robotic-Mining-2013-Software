#ifndef LED_H
#define LED_H


static Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


void initializeLeds()
{
    pwm.begin();
    pwm.setPWMFreq(1600);
}

void updateLeds()
{
    if(stateControl == 0)
    {
        pwm.setPWM(0, 0, 0);
        pwm.setPWM(1, 0, 0);
        pwm.setPWM(3, 0, 0);
        pwm.setPWM(4, 0, 0);
        pwm.setPWM(2, 0, 1600);
        pwm.setPWM(5, 0, 1600);
    }
    else if(stateControl == 1)
    {
        pwm.setPWM(1, 0, 0);
        pwm.setPWM(2, 0, 0);
        pwm.setPWM(4, 0, 0);
        pwm.setPWM(5, 0, 0);
        pwm.setPWM(0, 0, 1600);
        pwm.setPWM(3, 0, 1600);
    }
    else if(stateControl == 2)
    {
        pwm.setPWM(0, 0, 0);
        pwm.setPWM(2, 0, 0);
        pwm.setPWM(3, 0, 0);
        pwm.setPWM(5, 0, 0);
        pwm.setPWM(1, 0, 1600);
        pwm.setPWM(4, 0, 1600);
    }
}

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
        //stateControl++;
        //if(stateControl == 3)
        //stateControl = 0;

        previous = current;
        state = !state;
        digitalWriteFast(13, state);
    }

}

#endif
