/**
 * Main program with setup and loop
 */
#include "Arduino.h"
#include "conf/coreManager.h"
#include "conf/station_conf.h"
#include "conf/ap_conf.h"

#include "station_mode.h"
#include "ap_mode.h"

void setup() {
  Serial.begin(115200);
  delay(5000);

  initApMode();
}

void loop() {
  setApMode();
}
