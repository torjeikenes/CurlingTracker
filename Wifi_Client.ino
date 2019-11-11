#include<ESP8266WiFi.h>
#include<SoftwareSerial.h>
SoftwareSerial mySerial(2,3); 
void setup(){  
  mySerial.begin(9600);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup Done");
}

void loop() {
  int n=WiFi.scanNetworks();
  if(n==0){
    Serial.println("No network found");
    Serial.write("No network found");
  }
   else
   {
    for(int i=0;i<n;++i)
    {
      if(WiFi.SSID(i)!="NodeMCU01")
        continue;
      Serial.print(WiFi.RSSI(i));

    }
   }

}
