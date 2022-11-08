#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <TMRpcm.h> 

//CS is connected to digital 3 
//SCK connected to digital pin 13
//MOSI connected to digital 11
//MISO connected digital pin 12
//Speaker connected to digital pin 9
//SDA is pin 4 analog
//SCL pin 5 analog
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
//const int interruptPin = 2;

#define SD_ChipSelectPin 4 
TMRpcm tmrpcm;  
void setup() {
    // Setting the outputs
  Serial.begin(57600);
  if (tcs.begin()){
    Serial.println("Found Sensor");
  }else {
    Serial.println("No sensor found");
    while(1);
  }
      tmrpcm.speakerPin = 9;      
  tmrpcm.setVolume(6);                     //define speaker pin. 
                                          //you must use pin 9 of the Arduino Uno and Nano
                                          //the library is using this pin
   if (!SD.begin(SD_ChipSelectPin)){     //see if the card is present and can be initialized
    
    return;
   }
}

void loop(void) {
  uint16_t red, green, blue, clear;
  float average, r, g, b;

  //tcs.setInterrupt(false);  //turn on led
  delay(100);   //takes 50ms to read 
  tcs.getRawData(&red, &green, &blue, &clear);
  //tcs.setInterrupt(true);   //turn off led

  average = (red+green+blue)/3;
  r = red/average;
  g = green/average;
  b = blue/average;

  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  //Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

if(r>1.95 && g<0.55 && b<0.55){
  tmrpcm.play("RP.wav"); 
  Serial.print("Detected Colore RED");
  delay(6000);
}
if(r<0.9 && g>1.4 && b<1.1){
  tmrpcm.play("GP.wav");
  Serial.print("Green Colore GREEN");
  delay(4000);
}
if(r<0.55 && g<1 && b>1.55){
  tmrpcm.play("BP.wav");
  Serial.print("Detected Colore BLUE");
  delay(5000);
}
if(r>1.35 && r<1.55 && g>1 && g<1.2 && b>0.4 && b<0.5){
  tmrpcm.play("YP.wav");
  Serial.print("Detected Colore YELLOW");
  delay(4000);
}
if((r>1.85) && ( g<0.755 && g>0.65) && (b<0.44 && b>0.35)){
  tmrpcm.play("OP.wav");
  Serial.print("Detected Colore ORANGE");
  delay(5000);
}
}
