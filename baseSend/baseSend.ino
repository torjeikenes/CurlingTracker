#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
 
const byte address[][6] = {"Node1"};
bool ok = false;
 
float findDist(String s) {
    int rssi = s.toInt();
    float dist = exp((rssi + 54.102)/-9.585);
    return dist;
}

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);
    delay(5000);
    Serial.print("Setup Complete");

    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
}
 
void loop(){
    String IncomingString="";
    boolean StringReady = false;

    while (mySerial.available()){
        Serial.println("fett");
        IncomingString=mySerial.readString();
        StringReady= true;
    }
    
    if (StringReady){
        float dist1 = findDist(IncomingString);
        Serial.println("If going to crash into eachother");
        Serial.println(dist1);

        //radio.startListening();
        //delay(100);
        //if ( radio.available()) {
        //    Serial.println("Don't");
        //    while (radio.available()) {
        //        radio.read(&ok, sizeof(ok));
        //        if (ok) {
        //            Serial.println("ok");
        //            break;
        //        }
        //    }
        //}
        //radio.stopListening();
        delay(100);
        for (int i = 0; i <= 20; i++) {
            Serial.println("send");
            radio.write(&dist1, sizeof(dist1));
            delay(100);
        }
    }
    delay(10);
}
