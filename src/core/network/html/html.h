/*********************
Display HTML form
**********************/
String prepareHtmlPage()
{
  String htmlPage =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html><head><title>Wemos D1 Web-Server in AP Mode</title></head><body align=center>" +
            "<h1 align=center><font color=\"green\">Wemos D1 WiFi Web-Server in AP Mode</font></h1>" +
            "<form method='get'>" +
            "<label for='ssid'>SSID :</label>" +
            "<input type='text' id='ssid' name='ssid'>" +
            "<br>" +
            "<label for='password'>Key :</label>" +
            "<input type='text' id='password' name='password'>" +
            "<br>" +
            "<input type='submit' name='Submit' value='Connection'>" +
            "</form>" +
            "</html>" +
            "\r\n";
  return htmlPage;
}
