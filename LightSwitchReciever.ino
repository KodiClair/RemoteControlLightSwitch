 //nrf2401 receiver
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 nrf(9, 8);  // CE, CSN
const byte linkAddress[6] = "link1";  //address through which two modules communicate.
const byte greenLED = 10;
int data[1];

const int speedPin = 3 ;
const int in_1 = 4 ;
const int in_2 = 2 ;
const int mSpeed = 255;

volatile int recievedData;
/////////////////////////////////////////////////////////////////////
void setup()
{ 
  Serial.begin(9600); 
  Serial.println("Starting");
  pinMode(greenLED, OUTPUT);
 
  nrf.begin();    
  nrf.openReadingPipe(0, 5);  //set the address 
  nrf.startListening();   //Set nrf as receiver

  pinMode(speedPin,OUTPUT) ;  	//we have to set PWM pin as output
  pinMode(in_1,OUTPUT) ; 	//Logic pins are also set as output
  pinMode(in_2,OUTPUT) ;
}
///////////////////////////////////////////////////
void loop() {
  
  recievedData = data[0];

  if (nrf.available())  //Read the data if available in buffer
     {
      nrf.read(&data, sizeof(data));
     }  
  
  Serial.println(recievedData); // reading data although transmitter is off

  switch (recievedData) {
    case 0:
      turnOff();
      break;
    case 1:
      turnOn();
      break;
    default:
      break;
  }

  delay(1000);

}
//////////////////////////////////////////////
void turnOn() {
  digitalWrite(in_1, HIGH);
  digitalWrite(in_2, LOW);
  analogWrite(speedPin, mSpeed);
  delay(1000);
  digitalWrite(in_1,HIGH);
  digitalWrite(in_2,HIGH);
}

void turnOff() {
  digitalWrite(in_1, LOW);
  digitalWrite(in_2, HIGH);
  analogWrite(speedPin, mSpeed);
  delay(1000);
  digitalWrite(in_1,HIGH);
  digitalWrite(in_2,HIGH);
}