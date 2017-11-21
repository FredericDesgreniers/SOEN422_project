# Proof of Concept - Team Cerberus
In this stage of the project we set out to build a small test setup using the hardware obtained. This would allow us to build the Web UI and communication components congruently with the engineering of the full scale device and proide the necessary knowledge to build a full system.

### Table of Contents
1. [Contributors](#Contributors)
2. [Test Unit](#test-unit)
3. [Results](#results)
4. [Future Rquirements](#Future-Rquirements)
5. [Figures](#Figures)

## Contributors
**Name** | **ID**
:--:|---
Christopher McArthur | `40004257`
Frederic Desgreniers | `40016777`

## Test Unit
Using the Arduino Nano Rev3, an HX711 and a 10kg load cell we built a small scale to prove that we can be able to register the force applied to the strain gauge. See [figure 1](#figure-1) for reference. Determining how to correctly wire the load cell to the HX711 and connecting that to the Arduino possed several challenges as some resources used different wire layouts. The diagram below shows the correct layout: ![image](https://user-images.githubusercontent.com/16867443/33037631-3e270aba-ce00-11e7-8021-49ecf45f58b2.png)

## Results
Using the [HX711 Library](https://github.com/bogde/HX711) and some sample code provided for the HX711 by [SparkFun](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) we were able to successfully calibrate the scale to accurately weigh a 3 and 10 pouns weights.

## Future Rquirements
* [Combinator Board](http://www.robotshop.com/ca/en/load-sensor-combinator-v11.html)
* [50kg Load Cell](http://www.robotshop.com/ca/en/micro-load-cell-50-kg.html) X4 (Seriouly four)

The goal is to measure the force delivered with a punch (by a retired amature kickboxer). In order to do this we need to have load cells which will be able to capture that quantity of force. We have settled for 4 x 50kg load cells giving a total of 440lbs. These will make the engineering more simple compared to using other types of strain gauges. The proposed design will feature two circular plates that will be bolts to the load cells. The top plate will be half the diameter of the bottom plate. The direction of the load cells will be places in the center to register the force applied to the top plate. See [figure 2](#figure-2) and [figure 2](#figure-2) for a visual. The 4 x 50kg load cells will be connected with a combinator board which is required to have all four work as one which will then be connected to the HX711 and the Nano.

## Figures

### Figure 1
![20171120_114834](https://user-images.githubusercontent.com/16867443/33049867-0507c6fe-ce30-11e7-84e0-2e0c05b6bfcf.jpg)

### Figure 2
![image](https://user-images.githubusercontent.com/16867443/33038124-a067f7a6-ce01-11e7-8dc8-f3b6b804d6f7.png)

### Figure 3
![image](https://user-images.githubusercontent.com/16867443/33041120-3b722c0e-ce0b-11e7-9288-a1fb9656be01.png)
