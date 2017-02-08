
#include <SparkTime.h>

// ASlapAlarmClock

//Pin setup
int relayPin = D6;
int buzzerPin = D5;
int lightSensorPin = A3;

//Time related variables
String alarmTime = "";  //time set in the html page
String currentTime = ""; //current time

//Sound Buzzer related variables
int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

//Light Sensor related variables
// Defines the light-sensor threshold value( we obtained this value while testing the light sensor)
//If you increase this value, the sensor will be less sensible to light
//If you decrease this value, the sensor will be more sensible to light
int thresholdvalue = 400;

//Boolean that says if alarm is ON/OFF(set/not set)
bool alarmEnabled = true;


void setup()
{
  //Setting output pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(D7, OUTPUT);
  
  // This is saying that when we ask the cloud for the function "alarm", it will employ the function setAlarm() from this app.
  Particle.function("alarm", setAlarm);

  //THis sets the timezone
  Time.zone(-2.0);
}


void loop()
{
    //Checks if the alarm is set
    if(alarmEnabled){
        //If alarm is set -> get current time
        currentTime = getCurrentTime();
        //When its time to get slapped.Opsss,  I mean, wake up...
        if(alarmTime == currentTime){
            
            // Read the value of the light sensor.
            int sensorValue = analogRead(lightSensorPin);
        
            // Deactivate the relay if the sensor value is above threshold
            if (sensorValue > thresholdvalue)   
            {
        
                digitalWrite(relayPin, LOW);
                digitalWrite(D7, LOW);
                alarmEnabled = false;
                
            }
            //activate the relay if the sensor value is below threshold
            else   
            {
                digitalWrite(relayPin, HIGH);
                digitalWrite(D7, HIGH);
                
                //Play alarm tone
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
                    if( analogRead(lightSensorPin) > thresholdvalue){
                        break;
                    }
                }
            }
        }
    }
   
}

//This method sets the alarm to the given time. This is the method that is executed when we make a call for the cloud
int setAlarm(String aux)
{
    alarmTime = aux;
    alarmEnabled = true;
    return 1;
}

//This method returns a string of the current time in the format hh:mm
String getCurrentTime()
{
    String currTime = "";
    String hour = String(Time.hour());
    String minute = String(Time.minute());
    
    if(hour.length() < 2){
        currTime.concat("0");
        currTime.concat(hour);
    }else{currTime.concat(hour);}
    currTime.concat(":");
    if(minute.length() < 2){
        currTime.concat("0");
        currTime.concat(minute);
    }else{currTime.concat(minute);}
    
    return currTime;
}

//Method that plays a given tone
void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(buzzerPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(buzzerPin, LOW);
        delayMicroseconds(tone);
    }
}

//Method that plays a note for the given tones
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
