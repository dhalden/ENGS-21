#include <Ultrasonic.h>
#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Ultrasonic.h"



int count;
int speakerOut = 8;



Ultrasonic ultrasonic(7,6);
int buttonPin = 2;
long reg_dist;

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(speakerOut,OUTPUT);
  delay(5000);
  reg_dist = -1;
}

void loop()
{
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.Ranging(CM);// get the current signal time;
  if(reg_dist < 0 || digitalRead(buttonPin)) {
    reg_dist = RangeInCentimeters;
  }
  else if (reg_dist - RangeInCentimeters > 10) {
    Serial.println("The distance to obstacles in front is: ");
    Serial.print(RangeInCentimeters); //0~400cm
    Serial.println(" cm");
    for (count=0;count<250;count++) 
    {
      digitalWrite(speakerOut,1);
      delayMicroseconds(1000);
      digitalWrite(speakerOut, 0);
      delayMicroseconds(1000);
    }
  }
  else {
    Serial.println("The reg_dist is: ");
    Serial.print(reg_dist);
    Serial.println(" cm");
  }
}


