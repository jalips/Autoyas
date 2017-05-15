/*********************
Read file for conf
**********************/
int readFile(){
    // Open file and read its contents, print to serial monitor-
    SerFlash.begin();
    int32_t retval = SerFlash.open(wifi_file_name, FS_MODE_OPEN_READ);
    String text_file = SerFlash.readBytes();
    Serial.print("Read ");
    Serial.print(text_file.length());
    Serial.println(" bytes from "+wifi_file_name+" - contents:");
    Serial.println(text_file);
    SerFlash.close();
    SerFlash.freeString();

    int text_index = text_file.indexOf('&');

    String text_ssid = text_file.substring(0,text_index--);
    Serial.println("Mon texte SSID du fichier : "+text_ssid);

    text_file.replace(text_ssid+"&", "");
    //text_get.replace("%21","!");
    Serial.println("Mon texte Key du fichier : "+text_file);

    html_ssid = text_ssid;
    html_password = text_file;

    if(html_ssid.compareTo("") == 0 && html_password.compareTo("") == 0){
        return 1;
    }else{
        return 0;
    }
}

/*********************
Write File
**********************/
void writeFile(String ssid, String key){
    Serial.println("Open file");
    SerFlash.begin();
    // Create a file
    int32_t retval = SerFlash.open(wifi_file_name,
        FS_MODE_OPEN_CREATE(512, _FS_FILE_OPEN_FLAG_COMMIT));

    if (retval == 0) {
        Serial.println("Write file");
        // Write our String object to the file!
        SerFlash.write(ssid+" & "+key);
        SerFlash.close();
    }

    readFile();
}

/*********************
Delete File
**********************/
void deleteFile(){
    SerFlash.begin();
    int32_t retval = SerFlash.del(wifi_file_name);
    Serial.print("Deleting "+wifi_file_name+" return code: ");
    Serial.println(SerFlash.lastErrorString());
    Serial.flush();
}
