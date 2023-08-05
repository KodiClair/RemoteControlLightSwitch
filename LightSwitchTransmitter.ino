//nrf2401 transmitter:
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 nrf(9, 8);  // CE, CSN

const byte linkAddress[6] = "link1";

volatile bool switchState;

int data[1];
char charVal[17];
////////////////////////////////////////////////////
void setup()
{
  pinMode(4, INPUT);
  Serial.begin(9600);
  Serial.println("NRF24L01 link");
  nrf.begin();   
  nrf.openWritingPipe(5);  //set the address 
  //nrf.setPALevel(RF24_PA_LOW);   //keep tx level low to stop psu noise, can remove this but then put in decoupling caps
  // Options are: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm,  RF24_PA_HIGH=0dBm.
  nrf.setPALevel(RF24_PA_HIGH); 
  nrf.stopListening();  //act as a transmitter
}
///////////////////////////////////////////////////
void loop()
{  
  switchState = digitalRead(4);
  Serial.println(switchState);
  data[0] = switchState;
  nrf.write(data, sizeof(data));
   //spit out the data array
  
  delay(1000);
}
/////////////////////////////////////////////////

void transmit(void) {
  Serial.println("Transmitting");
}