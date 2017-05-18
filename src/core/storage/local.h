/************************************************************************
* Functions for CRUD a file
***********************************************************************/

#include "FS.h"

String wifi_file_directory = "/";
String wifi_file_name = "wifi.txt";
String wifi_file = wifi_file_directory+wifi_file_name;

void initSetupFile(){
  if(SPIFFS.begin()){
    Serial.println("File system was mounted successfully");
  }
}

/*********************
Read file for conf
**********************/
int isFile(){
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    String fileName = dir.fileName();
    //size_t fileSize = dir.fileSize();
    //Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), String(fileSize).c_str());
    if(fileName == wifi_file_name){
      Serial.println("There is file "+fileName);
      return 1;
    }
    Serial.println("There is no file "+wifi_file_name+ ", stay in AP Mode.");
    return 0;
  }
}

/*********************
Read file for conf
**********************/
String readFile(){
  Serial.println("====== Reading from SPIFFS file =======");
  String s = "";
  // open file for reading
  File f = SPIFFS.open(wifi_file, "r");
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
  File f = SPIFFS.open(wifi_file, "w");
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
  if(SPIFFS.remove(wifi_file)){
    Serial.println("file deleted");
  }else{
    Serial.println("file not deleted");
  }
}
