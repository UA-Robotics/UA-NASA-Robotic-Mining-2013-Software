#ifndef COMM_H
#define COMM_H

//These are the structures responsible for communication

//data storing the motor data
struct MotorData
{
    int leftMotorSpeed;
    int rightMotorSpeed;
    int actuatorSpeed;
};

static MotorData motor;

int leftMotorSpeed = 127;
int rightMotorSpeed = 127;
int actuatorSpeed = 127;

EasyTransfer communicationBoardIn;

void initializeCommunication()
{
    Serial.begin(9600);

    communicationBoardIn.begin(details(motor), &Serial);
}

static boolean communicationSafety(boolean state)
{
    static boolean storedState = false;
    static unsigned long previous = 0;
    static unsigned long current = 0;

    current = millis();

    if(current - previous > 1000)
    {
        storedState = false;
    }

    if(state)
    {
        previous = current;
        storedState = true;
    }

    return storedState;
}

static void getData()
{
    if(communicationBoardIn.receiveData())
    {
        communicationSafety(true);
        leftMotorSpeed = motor.leftMotorSpeed;
        rightMotorSpeed = motor.rightMotorSpeed;
        actuatorSpeed = motor.actuatorSpeed;
    }
}

void passData()
{
    if(!communicationSafety(false))
    {
        leftMotorSpeed = 127;
        rightMotorSpeed = 127;
        actuatorSpeed = 127;
    }
}

void updateCommunication()
{
    getData();
    passData();
}

#endif
