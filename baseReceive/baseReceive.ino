#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
 
#include <math.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
RF24 radio(7, 8); // CE, CSN
 
const byte address[][6] = {"Node1"};
float dist1 = 0;
float dist2 = 0;
 
float finnPosisjonenY(float d2,float d3){  //Funksjon som returnerer x-verdien
    float d1=5;                                   //lengden mellom basestasjonene
    float y;

    if (d2+d3 < d1) {
        y = 0;
    } 
    else {
        y=(pow(d1,2)+pow(d2,2)-pow(d3,2))/(2*d1);   //formel
    }
    return y;
}

float finnPosisjonenX(float d2,float d3){  //Funksjon som returnerer y-verdi
    float d1=5;
    float x;

    if (d2+d3 < d1) {
        x = d1/2;
    } 
    else {
        x=sqrt(pow(d2,2)-pow(finnPosisjonenY(d2,d3),2));    //formel
    }
    return x;
}

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
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening(); 
}

void loop(){
    String IncomingString="";
    boolean StringReady = false;

    if (mySerial.available()){
        IncomingString=mySerial.readString();
        StringReady= true;
    }

    if (StringReady){
        float dist2 = findDist(IncomingString);
        Serial.print("dist2 ");
        Serial.println(dist2);
        //radio.stopListening();

        //bool ok = true;

        //delay(1000);
        //radio.write(&ok, sizeof(ok));

        //radio.startListening();
        //delay(100);
        if (radio.available()) {
         	radio.read(&dist1, sizeof(dist1));
            Serial.print("dist1 ");
            Serial.println(dist1);
        }
        delay(100);
        float x = finnPosisjonenX(dist1,dist2);
        float y = finnPosisjonenY(dist1,dist2);

        Serial.print("X: ");
        Serial.print(x);
        Serial.print("Y: ");
        Serial.println(y);
    }
    delay(10);
}
