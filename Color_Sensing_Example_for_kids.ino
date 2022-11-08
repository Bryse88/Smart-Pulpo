
#include <Wire.h>                                                 //include the I2C library to communicate with the sensor
#include "Adafruit_TCS34725.h"                                    //include the sensor library


#define redpin 3                                                  //pwm output for RED anode use 1K resistor
#define greenpin 5                                             //pwm output for GREEN anode use 2K resistor
#define bluepin 6                                              //pwm output for BLUE anode use 1K resistor



#define commonAnode false                                         // set to false if using a common cathode LED                     



byte gammatable[256];                                             // our RGB -> eye-recognized gamma color

                                                                  //Create an instance of the TCS34725 Sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);                                             //Sart serial comms @ 9600 (you can change this)
  Serial.println("Color View Test");                              //Title info             

  if (tcs.begin()) {                                              //if the sensor starts correctly
    Serial.println("Found sensor");                               //print the happy message
  } else {                                                        //if the sensor starts incorrectly
    Serial.println("No TCS34725 found ... check your connections");//print the not so happy message
    while(1);
     }
  }
  


void loop() {
  uint16_t clear, red, green, blue;                                 //declare variables for the colors

  tcs.setInterrupt(false);                                          // turn on LED

  delay(60);                                                        // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clear);                      //read the sensor

  tcs.setInterrupt(true);                                           // turn off LED
  
  Serial.print("C:\t"); Serial.print(clear);                        //print color values
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);

                                                                    // Figure out some basic hex code for visualization
}         
