/*
 * UART    : LED (used as Software PWM pin)
 * I2C     : -
 * D18/D19 : Touch (used as interrupt pin)
 * A2/A3   : Potentiometer
 */

#include <Arduino.h>

const int pinButton     = PIN_D19;
const int pinLed        = PIN_D00;
const int potentiometer = A3;

int toggleSwitch = 0;

void pushed()
{
  toggleSwitch = toggleSwitch ? 0 : 1;
}

void setup()
{
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT);

  attachInterrupt(pinButton, pushed, FALLING);
}

void loop()
{
  int value = analogRead(potentiometer);

  Serial.println(value);

  if (toggleSwitch) {
    /* Software PWM Control */
    analogWrite(pinLed, value);
  } else {
    analogWrite(pinLed, 0);
  }
}

