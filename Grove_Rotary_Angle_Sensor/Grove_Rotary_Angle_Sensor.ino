// demo of Starter Kit V2.0


const int potentiometer = A3;                    // rotary angle sensor connect to A3

void setup()
{
    Serial.begin(115200);                        // set the serial communication frequency at 115200 bits per sec
}

void loop()
{
    int value = analogRead(potentiometer);
    Serial.println(value);                      // pirnt the value on the serial monitor screen
    delay(100);                                  // wait 1000ms before printing next value
}
