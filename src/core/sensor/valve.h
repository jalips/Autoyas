/************************************************************************
* Method for valve sensor
***********************************************************************/

// This is the output pin on the Arduino we are usin
int solenoidPin = 14;

void setupValve(){
  //Sets the pin as an output
  pinMode(solenoidPin, OUTPUT);
}

void loopValveOn(){
  // Switch Solenoid ON
  digitalWrite(solenoidPin, HIGH);
  Serial.println("Valve ON");
}

void loopValveOff(){
  // Switch Solenoid OFF
  digitalWrite(solenoidPin, LOW);
  Serial.println("Valve OFF");
}
