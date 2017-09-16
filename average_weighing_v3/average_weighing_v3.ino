/*
 Setup your scale and start the sketch WITHOUT a weight on the scale
 Once readings are displayed place the weight on the scale
 Press +/- or a/z to adjust the calibration_factor until the output readings match the known weight
 Arduino pin 5 -> HX711 CLK
 Arduino pin 6 -> HX711 DOUT
 Arduino pin 5V -> HX711 VCC
 Arduino pin GND -> HX711 GND 
*/

#include "HX711.h"

HX711 scale(6, 5);

float calibration_factor = -375; // this calibration factor is adjusted according to my load cell
float units;
float ounces;

const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average


void setup() {
   Serial.begin(9600);
   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");
  units = scale.get_units(), 10;
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;
  Serial.print(units);
  Serial.print(" grams"); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  
  
  total = total - readings[readIndex];
  readings[readIndex] = units;

  /*for(int i = 0; i <10; i++)
{
  //Serial.println(readings[i]);
}*/
   
 
  // add the reading to the total:
  total = total + readings[readIndex];
  
  
  
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

   // calculate the average:
  //Serial.println(total);
  //Serial.println(numReadings);
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.print("moving average:");
  Serial.print(average);
  Serial.println(" grams");
  delay(1);        // delay in between reads for stability


  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }

   
  
 delay(100);

  
}
