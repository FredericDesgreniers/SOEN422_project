# Force Gauge - Team A
In this project we aimed to develop a force gauge which was capable of detecting the force applied from a human punch. This document outlines the goals of the project, the design of the system, and the final resulting prototype which was delivered.

> To best view this document, use the [link](https://github.com/FredericDesgreniers/SOEN422_project/blob/master/Docs/Full-Scale/README.md) provided.

### Table of Contents
1. [Contributors](#Contributors)
1. [Introduction](#introduction)
1. [Description](#Description)
   1. [Name](#name)
   1. [function](#function)
   1. [performance](#performance)
   1. [scope of complition](#scope-of-completion)
1. [hardware design](#hardware)
   1. [system]()
   1. [subsystems]()
   1. [intercommunication]()
1. [software design](#)
   1. [system design]()
   1. [subsystems]()
   1. [arduino functions]()
   1. [system communication]()
1. [development software/enviroments]()
1. [system delivery]()
   1. [initialisation]()
   1. [operation]()
1. [discussion]()
1. [Apendix]()

## Contributors
**Name** | **ID**
:--:|---
Christopher McArthur | `40004257`
Frederic Desgreniers | `40016777`

## Description
This force gague system, called the **Punch O-Meter**, is designed to be placed into any punching bag and display live results of the forces being applied. The system would include a web server and with an internet connection allowing users to view the data from their computer or mobile device. This data is the _force_ currently applied to the bag which is being captured by a microcontroller of the force gauge(s) set up in the bag. It is designed to capture the force from various types of punchs, meaning it is responsive enough to capture a quick double jab and strong enough to handle a left hook. Users are able to display the force in pounds, kilos, or newtons and track sessions to see the greatest force applied during their training.

The project succeded is producing a functional prototype which was able to capture the force applied and displayed the results through a web interface. However the lantency of the system was never refined to be low enough to capture a punch reliably.

## Hardware Design
The main hardware component is the force gauge itself, this went through many phases thought stuck with the initial concept of usign fource loadcells to mesure the weight (ie force) being applied. The first step was a proof of concept model which used a single loadcell as a scale and printed the weight. The loadcell was a wheatestone bridge type which was connected to an HX711; a specialized amplifer for these types of loadcells. The output of the HX711 was digital and made it easily captured by an Arduino Nano which used serial (UART) communication to desplay the results on a monitor.

The concept model was two circular plates with the four loadcells in between positioned an equal distance for the center and aligned at 90 degrees. This layout was changed early on in the development of the full scale model for serval factors:
- Calculating the geometry of the system was more complex
- Limitations in supply/availibilty of material (turn rectangles into circles)

For these reasons we opted for two rectangular plates; the top plate is `3x4x1/4` and the bottom plate is `5x4x1/4`. The top plate is centered over the bottom plate with an inch margin on the left and right sides of the force gauge.


## Design
**Components** | **Dimensions (in)**
:---:|---
Top plate | 3x3x1/4
front bolt | 1/32x1/2 
load cell | 2+1/16x1/2x1/2
back bolt | 1/32x1
bottom plate | 5x5x1/4

### Top Bolt 
- Pacement
  * center of bolt 3/4 frrom corner towards center
- Installation *{ TO BE FINALIZED }*
  1. through top plate, inset and grinded down... how to do this evenly... requires extra nut on inside
  2. weld to under side of top plate... how accurately can this be done?

## Results

## Figures
