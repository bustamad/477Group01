#include "HX711.h"

HX711 scale;
int calibration_factor = 5000;

void setup() 
{
  Serial.begin(9600);   // Starts serial communication in 9600 baud rate.

  Serial.println("Initializing scale calibration.");  // Prints user commands.
  Serial.println("Place weights");

  scale.begin(5,6);   

  scale.set_scale();
  scale.tare();          // Resets the scale to 0.
}
 

void loop() 
{

 
  scale.set_scale(calibration_factor);  // Adjusts the calibration factor.
 
  Serial.print("Reading: ");            // Prints weight readings in .2 decimal kg units.
  Serial.print(scale.get_units(),2);
  Serial.println(" kg");
  Serial.print("Calibration factor: "); // Prints calibration factor.
  Serial.println(calibration_factor);
  //if weight less than 5kg then power on motor
  if(scale.get_units() < 5.0)
  {
    pinMode(7,OUTPUT);
    digitalWrite(7,LOW);
  }
 
  if(Serial.available())  // Calibration process starts if there is a serial connection present.
  {
    char temp = Serial.read();    // Reads users keyboard inputs.
    
    if(temp == '+')      // Increases calibration factor by 10 if '+' key is pressed.
      calibration_factor += 10;
    else if(temp == '-') // Decreases calibration factor by 10 if '-' key is pressed.
      calibration_factor -= 10;
    else if(temp == 'c' || temp == 'C')
      scale.tare();                     // Reset the scale to zero if 'C' key is pressed.
  }

  scale.power_down();    // Puts the scale to sleep mode for 5 seconds.
  delay(5000);
  scale.power_up();
}


