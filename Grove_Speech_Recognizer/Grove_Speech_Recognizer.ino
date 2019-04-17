#include <Arduino.h>

#define USE_SOFTWARESERIAL
#ifdef USE_SOFTWARESERIAL

#include <SoftwareSerial.h>

// software serial : RX = digital pin 2, TX = digital pin 3
SoftwareSerial MySerial(2, 3);

#else

// hardware serial : RX = digital pin 0, TX = digital pin 1
#define MySerial Serial2

#endif

const char *voiceBuffer[] =
{
    "Turn on the light",
    "Turn off the light",
    "Play music",
    "Pause",
    "Next",
    "Previous",
    "Up",
    "Down",
    "Turn on the TV",
    "Turn off the TV",
    "Increase temperature",
    "Decrease temperature",
    "What's the time",
    "Open the door",
    "Close the door",
    "Left",
    "Right",
    "Stop",
    "Start",
    "Mode 1",
    "Mode 2",
    "Go",
};

void setup()
{
    Serial.begin(115200);
    MySerial.begin(9600);
    //MySerial.listen(); /* If multiple software serial ports are used */
}

void loop()
{
    char cmd;

    if(MySerial.available())
    {
        cmd = MySerial.read();
        Serial.println(voiceBuffer[cmd - 1]);
    }
}
