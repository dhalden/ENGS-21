//Generic Grove Digital Input Test Code
//D6:  plug actuator into digital (blue) D6.   Upload.  Open Serial monitor.
//Value is displayed in Arduino Serial monitor window (icon upper right of Arduino 1.0) twice a second
//
//NOTE: never use digital pins 0/1 for general digital inputs (they are also serial comm RX/TX); 
//Dartmouth Thayer School April 2012 cgl

const int DIpin=6;                    //define where actuator is - Digital Input Pin number (D6)
void setup()
{
  Serial.begin(9600);                //initializes display on Serial Monitor at 9600 baud
  pinMode(DIpin,INPUT);              //Defines this plug(pin) as an input (Arduino will read from it)
}
   void loop(){                         //All code in this loop repeats forever (until power reset)
   int sensorValue=digitalRead(DIpin);  //read sensor value (0 or 1) into an variable named sensorValue
   Serial.println(sensorValue);         //print the resulting sensor value in serial monitor window
   if(sensorValue) {
     Serial.println("You moved!");
   }
                      //wait 500/1000 = 1/2 a second
}                                       //goes back to start of loop
