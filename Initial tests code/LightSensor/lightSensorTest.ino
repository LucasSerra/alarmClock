//Using the Serial Monitor, this program enables the user to determine a threshold value
//that says if the room light is on/off.

  // Light Sensor pin
  const int pinLight = A0;
  void setup(){
    Serial.begin(9600);}
  void loop()
  {
      // Read the value of the light sensor. The light sensor is an analog sensor.
      int sensorValue = analogRead(pinLight);
      
      // Print sensorValue
      Serial.println(sensorValue);//Open Serial monitor to see
      
  }
