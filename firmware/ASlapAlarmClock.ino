
#include <SparkTime.h>

// ASlapAlarmClock

//Pin setup
int relayPin = D6;
int buzzerPin = D5;
int lightSensorPin = A3;

//Alarm related variables
String alarmTime = "";  //time set in the html page
String currentTime = ""; //current time
bool alarmEnabled = true;


void setup()
{

  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(D7, OUTPUT);

  Particle.function("alarm", setAlarm);

  Time.zone(-2.0);

  Serial.begin(9600);

}


void loop()
{
    if(alarmEnabled){
        currentTime = getCurrentTime();
        if(alarmTime == currentTime){
            digitalWrite(D7, HIGH);
            //TO-DO
            // Put motor/relay/sensor code here instead of turning on led
        }
    }
   
}


int setAlarm(String aux)
{
    alarmTime = aux;
    alarmEnabled = true;
    return 1;
}

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
