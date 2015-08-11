//These are the structures responsible for communication

//data to be received from the robot for control purposes
struct ControlData
{
    int leftMotorSpeed;
    int rightMotorSpeed;
    int actuatorSpeed;
    int stateControl;
};

//data storing the current state of the robot
struct StateData
{
    int errorState;
    int controlState;
    int power;
};

//data storing the motor data
struct MotorData
{
    int leftMotorSpeed;
    int rightMotorSpeed;
    int actuatorSpeed;
};

//state control variables
int leftMotorSpeed = 127;
int rightMotorSpeed = 127;
int actuatorSpeed = 127;

//The angle of the actuator
int angle;

//Control State
int stateControl = 0;

EasyTransfer controlET;
//EasyTransfer controlBoardIn;
EasyTransfer motorET;

static ControlData control;
//static StateData state;
static MotorData motor;

void initializeCommunicaton()
{
    Serial1.begin(38400);
    Serial3.begin(9600);

    //controlBoardIn.begin(details(state), &Serial1);
    controlET.begin(details(control), &Serial1);
    motorET.begin(details(motor), &Serial3);
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

static inline void getData()
{
    if(controlET.receiveData())
    {
        communicationSafety(true);
        leftMotorSpeed = control.leftMotorSpeed;
        rightMotorSpeed = control.rightMotorSpeed;
        actuatorSpeed = control.actuatorSpeed;
        stateControl = control.stateControl;
    }
}

static inline void sendData()
{
    if(communicationSafety(false))
    {
        motor.leftMotorSpeed = leftMotorSpeed;
        motor.rightMotorSpeed = rightMotorSpeed;
        motor.actuatorSpeed = actuatorSpeed;
    }
    else
    {
        motor.leftMotorSpeed = 127;
        motor.rightMotorSpeed = 127;
        motor.actuatorSpeed = 127;
        stateControl = 0;
    }

    motorET.sendData();
    //controlBoardIn.sendData();
}

void updateCommunication()
{
    getData();
    sendData();
}
