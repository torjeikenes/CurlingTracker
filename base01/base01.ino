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

 
RF24 radio(7, 8);               // nRF24L01 (CE,CSN)
 
RF24Network network(radio);

 
const uint16_t this_node = 00;
const uint16_t master00 = 01;
 
 
void setup() {
    SPI.begin();
    radio.begin();
    network.begin(90, this_node);  //(channel, node address)
    radio.setDataRate(RF24_2MBPS);
    Serial.begin(9600);
}
 
void loop() {
    network.update();
    // Send to master
    int len1 = 400;
    RF24NetworkHeader header2(master00);     
    bool ok = network.write(header2, &len1, sizeof(len1)); 
}
