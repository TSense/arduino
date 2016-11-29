#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi
char* ssid = "ieeehotspot";
char* password = "Jk638td9og35";

ESP8266WebServer server(7568);  // Define port 80 for the web server port

void respond() {
  String s = "";
  s += WiFi.macAddress();
  s += ";";
  s += (rand() % 15) + 15;
  s += ";";
  s += rand() % 100;
  s += ";";
  server.send(200, "text/html", s); // Send data as response
}

void configPage(){
  server.send(200, "text/html", "TSense Configuration Page");
}

void setup() {
  Serial.begin(115200); // Initializes serial with baud rate as a parameter
  int i = 0;
  WiFi.begin(ssid, password); // Sets Wifi credentials
  while (WiFi.status()  !=  WL_CONNECTED) { // Try to connect until it does
    delay(100);
  }
  Serial.println("");
  Serial.println(WiFi.localIP());   // Prints internal IP on serial TODO: Make it print on the LCD
  server.on("/temp", respond);          // Listen for HTTP/GET requests to respond appropriately
  server.on("/", configPage);
  server.begin();                   // Start web server
}

void loop() {
  server.handleClient();  // Makes sure to reconnect if wifi fails
}
