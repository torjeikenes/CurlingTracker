#include <SoftwareSerial.h> //importerer bibliotek for seriell kommunikasjon
SoftwareSerial mySerial(2, 3); // // setter opp pin 2, 3 som RX, TX

//importerer noen pakker for å kommunisere med nrf-modulen
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Velger hvilke porter som brukes for CE og CSN
RF24 radio(7, 8); 
 
const byte address[][6] = {"Node1"};
bool ok = false;
 
//Tar rssi som input og returnerer avstanden
float findDist(String s) {
    int rssi = s.toInt();

    //bruker formelen for avstand til basert på rssi
    float dist = exp((rssi + 54.102)/-9.585);
    return dist;
}

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600); //iverksetter kommunikasjonsprotokollen
    delay(5000);
    Serial.print("Setup Complete");

    radio.begin();                  // Aktiverer modulen
    radio.openWritingPipe(address); // Åpner kobling for å skrive til modulen
    radio.setPALevel(RF24_PA_MIN);  // Setter riktig antennestyrke
    radio.stopListening();          // Sier at modulen skal sende data
}
 
void loop(){
    String IncomingString=""; //resetter informajson fra forrige loop
    boolean StringReady = false;

    while (mySerial.available()){ //hvis det ligger data fra ESP-en i systemet
        IncomingString=mySerial.readString(); //hentes den og lagres som incomingstring
        StringReady= true;
    }
    
    if (StringReady){ //hvis den har hentet streng data fra ESP-en
        float dist1 = findDist(IncomingString); //finner avstanden
        delay(100);

        //sender avstanden 20 ganger
        for (int i = 0; i <= 20; i++) {
            radio.write(&dist1, sizeof(dist1));
            delay(100);
        }
    }
    delay(10);
}
