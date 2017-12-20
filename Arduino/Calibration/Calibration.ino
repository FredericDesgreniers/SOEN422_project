/*
MIT License

Copyright (c) 2017 Frederic Desgreniers, Christopher McArthur

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
THIS CODE IS A MODIFIED VERSION OF A CALIBRATION SKETCH
   By: Nathan Seidle
   From: SparkFun Electronics
   Date: November 19th, 2014
   License: I owe him a beer (Beerware license).
*/

#include "HX711.h"

HX711 scale(PD6, PD7);

//float calibration_factor = -103560;           // resonable with our 10kg
float calibration_factor = -6500;               // resonable with our 200kg

void setup() {
   pinMode(PD2, OUTPUT);
   Serial.begin(9600);
   Serial.println("HX711 calibration sketch");
   Serial.println("Remove all weight from scale");
   Serial.println("After readings begin, place known weight on scale");
   Serial.println("Press + or a to increase calibration factor");
   Serial.println("Press - or z to decrease calibration factor");

   scale.set_scale();
   scale.tare();                                // Reset the scale to 0
}

void loop() {

   scale.set_scale(calibration_factor);         // Adjust to this calibration factor

   Serial.print("Reading: ");
   Serial.print(scale.get_units(), 4);          // Read next input and print float with four decimal points
   Serial.print(" lbs calibration_factor: ");
   Serial.println(calibration_factor);

   if (Serial.available())
   {
      char temp = Serial.read();
      if (temp == '+' || temp == 'a')
         calibration_factor += 100;
      else if (temp == '-' || temp == 'z')
         calibration_factor -= 100;
      else if(temp == 't')
         scale.tare();

      Serial.println(temp);
   }

   delay(100);
}
