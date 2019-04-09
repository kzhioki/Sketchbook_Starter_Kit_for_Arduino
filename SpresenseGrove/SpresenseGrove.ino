#include <Arduino.h>

const int pinButton     = 19;       // pin of button define here
const int pinLed        = 0;        // pin of led define here
const int potentiometer = A3;       // rotary angle sensor connect to A3

void setup()
{
    Serial.begin(115200);           // set the serial communication frequency at 115200 bits per sec
    pinMode(pinButton, INPUT);      // set button INPUT
    pinMode(pinLed, OUTPUT);        // set led OUTPUT
}

void blinkLed(int pin)
{
  static int cnt = 0;

  if (cnt++ % 2)
    digitalWrite(pin, HIGH);
  else
    digitalWrite(pin, LOW);
}


void loop()
{
    int value = analogRead(potentiometer);

    if(digitalRead(pinButton))      // when button is pressed
    {
        blinkLed(pinLed);
        delay(value * 2);
    }
    else
    {
        digitalWrite(pinLed, LOW);
    }
}
