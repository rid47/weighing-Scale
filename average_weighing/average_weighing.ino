#include "HX711.h"

HX711 scale(6,5); //HX711 scale(6, 5);

float calibration_factor = -375;
float units;
float ounces;

const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average






void setup()
{
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  Serial.println("HX711 weighing");
  scale.set_scale(calibration_factor);
  scale.tare();
  Serial.println("Readings:");
}

void loop()
{
  Serial.print("Reading:");
  units = scale.get_units(),10;
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;

   // subtract the last reading:
  total = total - readings[readIndex];
  readings[readIndex] = ounces;

  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

   // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.print(average);
  delay(1);        // delay in between reads for stability


  

  
  //Serial.print(units);
  Serial.println(" grams");
  delay(1000);
}

