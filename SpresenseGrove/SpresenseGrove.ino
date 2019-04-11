/*
 * UART    : LED (used as GPIO pin)
 * I2C     : -
 * D18/D19 : Touch
 * A2/A3   : Potentiometer
 */

#include <Arduino.h>

const int pinButton     = PIN_D19;
const int pinLed        = PIN_D00;
const int potentiometer = A3;

void setup()
{
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT);
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

  if(digitalRead(pinButton)) // when button is pressed
    {
      blinkLed(pinLed);
      delay(value * 2);
    }
  else
    {
      digitalWrite(pinLed, LOW);
    }
}
