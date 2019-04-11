/*
 * UART    : LED (used as GPIO pin)
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
  digitalWrite(pinLed, toggleSwitch);
}

void setup()
{
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT);

  attachInterrupt(pinButton, pushed, FALLING);
}

void blinkLed(int pin, uint64_t msec)
{
  static uint8_t  signal = LOW;
  static uint64_t lastTime = 0;

  if ((millis() - lastTime) >= msec) {
    signal = (signal == LOW) ? HIGH : LOW;
    digitalWrite(pin, signal);

    lastTime = millis();
  }
}

void loop()
{
  int value = analogRead(potentiometer);

  Serial.println(value);

  if (toggleSwitch) {
    blinkLed(pinLed, value);
  } else {
    digitalWrite(pinLed, LOW);
  }
}

