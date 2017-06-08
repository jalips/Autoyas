/************************************************************************
* Method for water sensor
***********************************************************************/

// Le capteur est sur la pin A0
const int capteur = 0;

int loopWater(){
  // Lecture de la valeur du capteur
  int val = analogRead (capteur);
  Serial.println ("Water level : ");
  Serial.println (val);
  // Attendre 5s avant la prochaine lecture
  delay (1000);
  return val;
}
