#include <Ultrasonic.h>
#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Ultrasonic.h"

int count;
int speakerOut = 8;

// New instances of Ultrasonic of the form ultrasonic(trigger, echo)

// The main sensor for the actual stair
Ultrasonic ultrasonic(7, 6);

// The lower sensor to detect someone going up the steps
Ultrasonic ultrasonicLowerStep(5, 4);

int lowerStepTimeout;

long reg_dist;


void setup()
{
  Serial.begin(9600);
  pinMode(speakerOut,OUTPUT);
  
  // Wait 5s to detect the max distance for the upper sensor
  delay(5000);
  reg_dist = -1;
  lowerStepTimeout = 0;
}

void loop()
{
  long RangeInCentimeters;
  long lowerStepRangeInCentimeters;
  
  // get the current signal time
  RangeInCentimeters = ultrasonic.Ranging(CM);
  lowerStepRangeInCentimeters = ultrasonicLowerStep.Ranging(CM);
  
  // Set the reg_dist if this is the first run (i.e. not yet set)
  if (reg_dist < 0) {
    reg_dist = RangeInCentimeters;
  }
  
  // If someone is on the lower step (within 100cm)
  if (lowerStepRangeInCentimeters < 100)
    lowerStepTimeout = 3;
  
  // If someone is walking down
  // Trigger upper sensor and lowerStepTimeout is cleared
  else if ((reg_dist - RangeInCentimeters > 15) && (lowerStepTimeout == 0)) {
    Serial.println("The distance to obstacles in front is: ");
    Serial.print(RangeInCentimeters); //0~400cm
    Serial.println(" cm");
    
    // Turn on the speaker, C# 5 1/4 note
    tone(speakerOut, 554, 1000);
    delay(1000);
//    for (count=0; count < 250; count++) 
//    {
//      digitalWrite(speakerOut,1);
//      delayMicroseconds(1000);
//      digitalWrite(speakerOut, 0);
//      delayMicroseconds(1000);
//    }
  }
  
  // Either no one on step or walking up (lowerStepTimeout > 0)
  else {
    Serial.println("The reg_dist is: ");
    Serial.print(reg_dist);
    Serial.println(" cm");
  }
  
  if (lowerStepTimeout > 0) lowerStepTimeout--;
  
  delay(1000);
}


