#ifndef COMM_H
#define COMM_H

//These are the structures responsible for communication

//data to be sent to the robot for control purposes
struct ControlData
{
    int leftMotorSpeed;
    int rightMotorSpeed;
    int actuatorSpeed;
    int stateControl;
};

//data storing current state of the robot
struct StateData
{
    int errorState;
    int controlState;
    int power;
};

//Several declarations

//State Control Variables
int actuatorSpeed = 127;
int leftMotorSpeed = 127;
int rightMotorSpeed = 127;
int stateControl = 1;

EasyTransfer communicationBoardOut; //for sending commands to the robot
EasyTransfer controlET;  //for receiving data back from the robot

static ControlData control;  //control data to send to robot
static StateData state;  //get the state data from the robot

void initializeCommunicaton()
{
    Serial1.begin(38400);

    controlET.begin(details(control), &Serial1);
    //communicationBoardOut.begin(details(state), &Serial1);
}

static void updateData()
{
    control.leftMotorSpeed = leftMotorSpeed;
    control.rightMotorSpeed = rightMotorSpeed;
    control.actuatorSpeed = actuatorSpeed;
    control.stateControl = stateControl;
}

void updateCommunication()
{
    updateData();
    //communicationBoardOut.receiveData();
    controlET.sendData();
}

#endif
