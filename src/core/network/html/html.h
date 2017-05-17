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
            "\r\n"+
            "<!DOCTYPE HTML>" +
            "<html>" +
            "<head>" +
            "<title>Wemos D1 Web-Server in AP Mode</title>" +
            "<meta name='viewport' content='width=device-width, initial-scale=1.0'>" +
            "</head>" +
            "<style>" +
            "body {" +
            "  text-align: center;" +
            "  padding: 50px 0;" +
            "}" +
            "h1 {" +
            "  color: lightseagreen;" +
            "  font-size: 2rem;" +
            "}" +
            ".input-field {" +
            "  position: relative;" +
            "  margin-top: 2rem;" +
            "}" +
            ".input-field label {" +
            "  color: grey;" +
            "  position: absolute;" +
            "  top: -1rem;" +
            "  left: 0;" +
            "  font-size: 1rem;" +
            "  cursor: text;" +
            "  transition: .2s ease-out;" +
            "  text-align: initial;" +
            "}" +
            "input {" +
            "  background-color: transparent;" +
            "  color: lightseagreen" +
            "  border: none;" +
            "  border-bottom: 1px solid grey;" +
            "  border-radius: 0;" +
            "  outline: none;" +
            "  height: 3rem;" +
            "  width: 100%;" +
            "  font-size: 1rem;" +
            "  margin: 0 0 20px 0;" +
            "  padding: 0;" +
            "  box-shadow: none;" +
            "  box-sizing: content-box;" +
            "  transition: all 0.3s;" +
            "}" +
            "input:focus {" +
            "  border-bottom: 1px solid lightseagreen;" +
            "  box-shadow: 0 1px 0 0 lightseagreen;" +
            "}" +
            ".btn {" +
            "  width: auto;" +
            "  color: white;" +
            "  background-color: lightseagreen;" +
            "  text-align: center;" +
            "  letter-spacing: .5px;" +
            "  transition: .2s ease-out;" +
            "  border: none;" +
            "  border-radius: 2px;" +
            "  display: inline-block;" +
            "  height: 3rem;" +
            "  line-height: 3rem;" +
            "  padding: 0 2rem;" +
            "  text-transform: uppercase;" +
            "  vertical-align: middle;" +
            "  -webkit-tap-highlight-color: transparent;" +
            "  box-shadow: 0 2px 2px 0 rgba(0,0,0,0.14), 0 1px 5px 0 rgba(0,0,0,0.12), 0 3px 1px -2px rgba(0,0,0,0.2);" +
            "}" +
            "</style>" +
            "<body>" +
            "<h1>Saisissez les informations de votre Wifi</h1>" +
            "<form method='get'>" +
            "<div class='input-field'>" +
            "<label for='ssid'>SSID :</label>" +
            "<input type='text' id='ssid' name='ssid'>" +
            "</div>" +
            "<div class='input-field'>" +
            "<label for='password'>Key :</label>" +
            "<input type='text' id='password' name='password'>" +
            "</div>" +
            "<input type='submit' name='Submit' value='Connection' class='btn'>" +
            "</form>" +
            "</html>" +
            "\r\n";
  return htmlPage;
}
