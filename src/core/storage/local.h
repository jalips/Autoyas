/************************************************************************
* Functions for CRUD a file
***********************************************************************/

#include "FS.h"

String wifi_file_name = "/wifi.txt";

void initSetupFile(){
  if(SPIFFS.begin()){
    Serial.println("File system was mounted successfully");
  }
}

/*********************
Read file for conf
**********************/
String readFile(){
  Serial.println("====== Reading from SPIFFS file =======");
  String s = "";
  // open file for reading
  File f = SPIFFS.open(wifi_file_name, "r");
  if (!f) {
    Serial.println("file open failed");
  }else{
    Serial.println("file open");
    s = f.readStringUntil('\n');
  }
  return s;
}

/*********************
Write File
**********************/
void writeFile(String ssid, String key){
  Serial.println("====== Writing to SPIFFS file =========");
  File f = SPIFFS.open(wifi_file_name, "w");
  if (!f) {
    Serial.println("file open failed");
  }else{
    Serial.println("file open");
    f.println(ssid+" & "+key);
  }
  f.close();
}

/*********************
Delete File
**********************/
void deleteFile(){
  if(SPIFFS.remove(wifi_file_name)){
    Serial.println("file deleted");
  }else{
    Serial.println("file not deleted");
  }
}
