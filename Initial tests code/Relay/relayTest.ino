// This program tests the Grove relay with a Grove Light Sensor
// If the light sensor reading is above the threshold, the relay is turned ON(closed)
// If the light sensor reading is below the threshold, the relay is turned OFF(opened)

// Define the pins to which the sensor and relay are attached.
const int pinLightSensor = A3;
const int relayPin =  8;

// Defines the light-sensor threshold value( we obtained this value while testing the light sensor)
int thresholdvalue = 400;

void setup()
{
    // Configure the relay's pin for output signals.
    pinMode(relayPin, OUTPUT);
}

void loop()
{
    // Read the value of the light sensor.
    int sensorValue = analogRead(pinLightSensor);

    // Activate the realy if the sensor value is above threshold
    if (sensorValue > thresholdvalue)   
    {
        digitalWrite(relayPin, HIGH);
    }
    else   
    {
        digitalWrite(relayPin, LOW);
    }
    delay(10);
}
