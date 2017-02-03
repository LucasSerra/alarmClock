// ASlapAlarmClock

#include <SparkTime.h>

//setando as portas correspondetes para cada dispositivo a ser ativado
int motor = D6;
int buzzer = D7;
int lightSensor = D3;
int hourSet;
int minuteSet;
bool set = false;

//string currentTime;
int hourCurrent;
int minuteCurrent;

void setup()
{

  pinMode(motor, OUTPUT);
  pinMode(lightSensor, INPUT);

  //Particle.function("alarm", setAlarm);

  //Particle.syncTime();

  Serial.begin(9600);

}


void loop()
{

  //if (alarm[SET] && alarm[HOUR] == Time.hour() && alarm[MINUTE] == Time.minute())
    getTime();


}


int setAlarm(bool set, int hourSet, int minuteSet)
{
/*
    hourCurrent = hourSet;
    minuteCurrent = minuteSet;
    set = true;
    //EXTRA ligar LED do Spark para confirmar
    return 1;
*/

}

void getTime()
{
  //time_t t = Time.now();
  Particle.syncTime();
  
  hourCurrent = Time.hour();
  minuteCurrent = Time.minute();
  
  Serial.println(Time.hour());

  

}
