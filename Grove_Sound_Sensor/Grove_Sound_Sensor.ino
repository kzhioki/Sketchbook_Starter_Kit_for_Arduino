// demo of Starter Kit V2.0 - Grove Sound Sensor
// when sound larger than a certain value, led will on

const int pinSound = A2;               // pin of Sound Sensor
const int pinLed   = 3;                // pin of LED

int thresholdValue = 50;                 // the threshold to turn on or off the LED

void setup()
{
    Serial.begin(115200);
    pinMode(pinLed, OUTPUT);            //set the LED on Digital 12 as an OUTPUT
}

void loop()
{
    int sensorValue = analogRead(pinSound);   //read the sensorValue on Analog 0
    Serial.println(sensorValue);
    if(sensorValue>thresholdValue)
        digitalWrite(pinLed,HIGH);
    delay(200);
    digitalWrite(pinLed,LOW);
}
