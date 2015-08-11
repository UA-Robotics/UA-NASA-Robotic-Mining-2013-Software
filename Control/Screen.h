#ifndef SCREEN_H
#define SCREEN_H

//initialize the screen communitcation
void initializeScreen()
{
    Serial.begin(38400);
}

//write the object update command to the screen
static void writeObject(byte object, byte index, unsigned int data)
{
    byte lsb = (data >> 0) & 0xFF;
    byte msb = (data >> 8) & 0xFF;

    byte checksum;

    Serial.write(0x01);
    checksum  = 0x01;
    Serial.write(object);
    checksum ^= object;
    Serial.write(index);
    checksum ^= index;
    Serial.write(msb);
    checksum ^= msb;
    Serial.write(lsb);
    checksum ^= lsb;
    Serial.write(checksum);
}

//this function updates the screen
void updateScreen()
{
    writeObject(0x07, 0x02, leftMotorSpeed);
    writeObject(0x07, 0x00, rightMotorSpeed);
}

#endif
