// This program tests the Grove relay with a Grove Light Sensor and a Groove Sound Buzzer
// If the light sensor reading is above the threshold, the relay and the buzzer are turned OFF(opened)
// If the light sensor reading is below the threshold, the relay and the buzzer are turned ON(closed)
// We used the Groove Starter Kit Buzzer example to code the buzzer

// Define the pins to which the sensor and relay are attached.
int pinLightSensor = A3;
int relayPin =  D6;
int speakerPin = D5;

int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;


void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(tone);
    }
}

void playNote(char note, int duration) {
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

    // play the tone corresponding to the note name
    for (int i = 0; i < 8; i++) {
        if (names[i] == note) {
            playTone(tones[i], duration);
        }
    }
}

// Defines the light-sensor threshold value( we obtained this value while testing the light sensor)
int thresholdvalue = 400;

void setup()
{
    // Configure the relay's pin for output signals.
    pinMode(relayPin, OUTPUT);
    pinMode(speakerPin, OUTPUT);
}

void loop()
{
    // Read the value of the light sensor.
    int sensorValue = analogRead(pinLightSensor);

    // Deactivate the realy if the sensor value is above threshold
    if (sensorValue > thresholdvalue)   
    {

        digitalWrite(relayPin, LOW);
        
    }
    //activate the realy if the sensor value is below threshold
    else   
    {
                digitalWrite(relayPin, HIGH);

         for (int i = 0; i < length; i++) 
        {
            if (notes[i] == ' ')
            {
                delay(beats[i] * tempo); // rest
            }
            else
            {
                playNote(notes[i], beats[i] * tempo);
            }

            // pause between notes
            delay(tempo / 2);
            if( analogRead(pinLightSensor) > thresholdvalue){
                break;
            }
        }
    }
    delay(10);
}