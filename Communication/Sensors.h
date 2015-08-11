#ifndef SENSORS_H
#define SENSORS_H

#define ACTUATOR 3
#define VIBRATOR 8


void initializeSensors()
{
    pinMode(ACTUATOR, INPUT);
    pinModeFast(VIBRATOR, OUTPUT);
}

static inline void actuatorUpdate()
{
    float volts = ((analogRead(ACTUATOR) / 1023.0) * 5.0) - 0.1;
    angle = volts * (90.0 / 3.0);
}

static inline void updateVibrators()
{
    if(angle > 70)
    {
        pinModeFast(VIBRATOR, LOW);
    }
    else
    {
        pinModeFast(VIBRATOR, HIGH);
    }
}

void updateSensors()
{
    actuatorUpdate();
    updateVibrators();
}

#endif
