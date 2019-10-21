/*
  NRF24L01 - Network
  Master
  modified on 8 Apr 2019
  by Saeed Hosseini @ Electropeak
  https://electropeak.com/learn/
*/
 
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include "dht.h"
 
RF24 radio(7, 8);               // nRF24L01 (CE,CSN)
 
RF24Network network(radio);
dht DHT;
 
const uint16_t this_node = 00;
const uint16_t node01 = 01;
const uint16_t node02 = 02;
 
 
void setup() {
    SPI.begin();
    radio.begin();
    network.begin(90, this_node);  //(channel, node address)
    radio.setDataRate(RF24_2MBPS);
    Serial.begin(9600);
}
 
void loop() {
    network.update();
    while ( network.available() ) {     // Is there any incoming data?
        RF24NetworkHeader header;
        unsigned long incomingData;
        network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
        if (header.from_node == 01) {    // If data comes from Node 02
          myservo.write(incomingData);  // tell servo to go to a particular angle
        }
}
