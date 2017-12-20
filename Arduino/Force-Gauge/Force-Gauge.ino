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

void setup() {
   Serial.begin(9600);
   scale.set_scale(-6500); // This value is obtained by using the SparkFun_HX711_Calibration sketch
   scale.tare();           // Assuming there is no weight on the scale at start up, reset the scale to 0
}

void loop() {
   Serial.println(scale.get_units(), 4); // scale.get_units() returns a float and print formated

   /// TODO: Read Serial.available()
}
