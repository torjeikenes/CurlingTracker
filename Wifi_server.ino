#include<WiFiClient.h>
#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include<SoftwareSerial.h>
const char *ssid="NodeMCU01";
const char *password="12345678";
ESP8266WebServer server(80);
//SoftwareSerial mySerial(2,3); 
void handleRoot()
{
  server.send(200,"text/html","<h1>connected</h1>");
}

void setup() {
  //mySerial.begin(9600);
  delay(1000);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP Adress: ");
  Serial.println(myIP);
  server.on("/",handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  Serial.write("WiFi Setup Complete");
}

void loop() {
  server.handleClient();
  //String IncomingString=".";
  //IncomingString=mySerial.readString();
  //Serial.print("1" + IncomingString);
}
