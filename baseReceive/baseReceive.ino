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
    float d1=10;                                   //lengden mellom basestasjonene

    float y=(pow(d1,2)+pow(d2,2)-pow(d3,2))/(2*d1);   //formel
    
    return y;
}

float finnPosisjonenX(float d2,float d3){  //Funksjon som returnerer y-verdi
    float d1=10;

    float x=sqrt(pow(d2,2)-pow(finnPosisjonenY(d2,d3),2));    //formel
    
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
        float x = finnPosisjonenX(7,7);
        float y = finnPosisjonenY(7,7);

        Serial.print("X: ");
        Serial.print(x);
        Serial.print("Y: ");
        Serial.println(y);

        x = finnPosisjonenX(0.7,0.7);
        y = finnPosisjonenY(0.7,0.7);

        Serial.print("X: ");
        Serial.print(x);
        Serial.print("Y: ");
        Serial.println(y);
        x = finnPosisjonenX(.2,2);
        y = finnPosisjonenY(.2,2);

        Serial.print("X: ");
        Serial.print(x);
        Serial.print("Y: ");
        Serial.println(y);
        x = finnPosisjonenX(.8,1);
        y = finnPosisjonenY(.8,1);

        Serial.print("X: ");
        Serial.print(x);
        Serial.print("Y: ");
        Serial.println(y);
    }
    delay(10);
}
