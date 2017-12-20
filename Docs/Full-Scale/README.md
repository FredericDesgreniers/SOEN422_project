# Force Gauge - Team A
In this project we aimed to develop a force gauge which was capable of detecting the force applied from a human punch. This document outlines the goals of the project, the design of the system, and the final resulting prototype which was delivered.

> To best view this document, use the [link](https://github.com/FredericDesgreniers/SOEN422_project/blob/master/Docs/Full-Scale/README.md) provided.

### Table of Contents
1. [Contributors](#contributors)
1. [Introduction](##force-gauge---team-a)
1. [Description](#description)
   1. [Name](#name)
   1. [Functionality](#functionality)
   1. [Performance](#performance)
   1. [Scope of Completion](#scope-of-completion)
1. [Hardware Design](#hardware-design)
   1. [System](#system)
   1. [Subsystems](#subsystems)
   1. [Intercommunication](#intercommunication)
1. [Software Design](#software-design)
   1. [System Design](#system-design)
   1. [Subsystems](#subsystems)
      1. [Arduino Functions](#arduino)
      1. [BeagleBone Functions](#beaglebone)
      1. [External Functions](#Web-Server)
   1. [System Software Communication](#system-software-communication)
1. [Development Software and Enviroments](#Development-Software)
1. [System Delivery](#system-delivery)
   1. [Initialisation](#system-initialisation)
   1. [Operation](#system-operation)
1. [Discussion](#discussion)
1. [Apendix](#apendix)

## Contributors
**Name** | **ID**
:--:|---
Christopher McArthur | `40004257`
Frederic Desgreniers | `40016777`

## Description
#### Name
This force gague system, called the **Punch O-Meter**, is designed to be placed into any punching bag and display live results of the forces being applied. 

#### Functionality
The system would include a web server and with an internet connection allowing users to view the data from their computer or mobile device. This data is the _force_ currently applied to the bag which is being captured by a microcontroller of the force gauge(s) set up in the bag. 

#### Performance
It is designed to capture the force from various types of punchs, meaning it is responsive enough to capture a quick double jab and strong enough to handle a left hook. Users are able to display the force in pounds, kilos, or newtons and track sessions to see the greatest force applied during their training.

#### Scope of Completion
The project succeded is producing a functional prototype which was able to capture the force applied and displayed the results through a web interface. However the lantency of the system was never refined to be low enough to capture a punch reliably. In addition the force gauge did experience some deformation under strong impacts, see [Figure 5](#figure-5), thought this did not degrade accuracy.

## Hardware Design
#### System
The system is comprised of three components; a force gauge, an arduino microcontroller, and a beaglebone black. Together they registered, interpolated and presented the data to provide a smooth user experience. Additionally an external machine was used to run the webserver to allow for better connectivity. An example of the system can seen in [Figure 4](#figure-4).

#### Subsystems
###### Force Gauge
The main hardware component is the force gauge itself, this went through many phases thought stuck with the initial concept of usign fource loadcells to mesure the weight (ie force) being applied. The first step was a proof of concept model, see [Figure 1](#figure-1), which used a single loadcell as a scale and printed the weight. The loadcell was a wheatestone bridge type which was connected to an HX711; a specialized amplifer for these types of loadcells. The output of the HX711 was digital and made it easily captured by an Arduino Nano which used serial (UART) communication to desplay the results on a monitor.

The concept model, see [Figure 2](#figure-2), was two circular plates with the four loadcells in between positioned an equal distance for the center and aligned at 90 degrees. This layout was changed early on in the development of the full scale model for serval factors:
- Calculating the geometry of the system was more complex
- Limitations in supply/availibilty of material (turn rectangles into circles)

For these reasons we opted for two rectangular plates; the top plate is `3x4x1/4` and the bottom plate is `5x4x1/4`. The top plate is centered over the bottom plate with an inch margin on the left and right sides of the force gauge. The top plate is smaller to provide a concentrate area to deliver the force as well as the requirements of the loadcell's placement.

###### HX711
This is the hardware which connects the force gauge to the arduino. it works by output a 5V to the loadcell and using the return voltage it calculates the resistence using an ADC, analog to digital conversion, which is translated to the weight in grams being stored on a 24-bit register. When the HX711 recieves a `HIGH` signal it performs a digital write of the next bit to be read.

###### Microcontrollers
**Arduino**'s role was to read and compute the data outputed from the force gauge through the amplifier. Reading the digital output it would convert this using offsets and scaling to determine the number of pounds which it would then output.

**BeagleBone**'s role was read the output from the arduino and forward the information to the web application using the network connection.

#### Intercommunication
**Force Gauge** --> **Arduino**: Wheatestone bridge senors like our load cells procude an analog output, this is passed though an amplifier, namely our HX711, which is designed to convert our analog output to a digital input for the arduino. In order to read all four load through one input of the HX711, the load cells were wired in parellel.

**Arduino** --> **BeagleBone**: In order to get the data onto the web server, we needed a network connection. Our arduino forwarded all the data through a UART communication with the beaglebone.

**BeagleBone** --> **Web Server**: Using it's network connection the BeagleBone would open a web socket with the web application and using HTTP post method is would tranmit the data would could then be added to the graph.

## Software Design
#### System Design
The software was responsible for transfering the values outputed by the scale from the arduino to the beaglebone and finalyl to the webserver. 

**Arduino**: a c++ program read the output data from the force gauge and forward the information to the beaglebone.

**BeagleBone**: a python program was used in order to bridge communication between the arduino and the web server used to render a chart of the force applied.

**Web Application**: Store a small history of the data points and display them on a graph showing the user the results of each impact.

#### Subsystems
###### Arduino
There are two main C++ applications used on the Arduino. The first is the calibration sketch which allows for the calculation of this calibration factor. The HX711 and its adjacent [library](https://github.com/bogde/HX711) output a digital value in grams, however this is not always true depending on the scale. In our case we wanted to use pounds as our units, as such we placed various weights on our scale and adjusted the `calibration_factor` until all the weight's were properly reported, see [Figure 4](#figure-4). The main application, in other words the one used for the system, uses the calculated `calibration_factor` and serial writes the data.

The key behind this is the [library](https://github.com/bogde/HX711) being utilized. The main application (using arduino for the UART) is as follows:
```C++
#include "HX711.h"

HX711 scale(PD6, PD7);

void setup() {
   Serial.begin(9600);
   scale.set_scale(-6500);
   scale.tare();
}

void loop() {
   Serial.println(scale.get_units(), 4);
}
```
Beginning with the instantiation of the `scale` we pass two pins; _DOUT_ or "Data OUTput" and _SCK_ or "Synchronized ClocK". Both pins have thier pin modes set to input and output respectively. Next we set our calibration factor but using `scale.set_scale(-6500)` which holds the value in a private member of the object and is used when `scale.get_units()` to convert the value read to our scale. With the scaling configured, we now call `scale.tare()` to remove the weigth of the top plates and any tension the system might be under. This tare method works by reading 10 values and calculating the average and once again sotring the value in a private member of the object. Within our loop our one and only HX711 library call is `scale.get_units()` which returns a float being the weight on the force gauge maped to out unit of choice. Behind the scene of the library, used by both `tare()` and `get_units()` is the `read()` functions which is the heart of the library because it is reponsible for exacting the values from the HX711 amplifier. The following snippet is the read function of the library.
```c++
long HX711::read() {
   // wait for the chip to become ready
   while (!is_ready()) { // bool HX711::is_ready() { return digitalRead(DOUT) == LOW; }
      // Will do nothing on Arduino but prevent resets of ESP8266 (Watchdog Issue)
      yield();
   }

   unsigned long value = 0;
   uint8_t data[3] = { 0 };
   uint8_t filler = 0x00;

   // pulse the clock pin 24 times to read the data
   data[2] = shiftIn(DOUT, PD_SCK, MSBFIRST);
   data[1] = shiftIn(DOUT, PD_SCK, MSBFIRST);
   data[0] = shiftIn(DOUT, PD_SCK, MSBFIRST);

   // set the channel and the gain factor for the next reading using the clock pin
   for (unsigned int i = 0; i < GAIN; i++) {
      digitalWrite(PD_SCK, HIGH);
      digitalWrite(PD_SCK, LOW);
   }

   // Replicate the most significant bit to pad out a 32-bit signed integer
   if (data[2] & 0x80) {
      filler = 0xFF;
   }
   else {
      filler = 0x00;
   }

   // Construct a 32-bit signed integer
   value = (static_cast<unsigned long>(filler) << 24
      | static_cast<unsigned long>(data[2]) << 16
      | static_cast<unsigned long>(data[1]) << 8
      | static_cast<unsigned long>(data[0]));

   return static_cast<long>(value);
}
```
At first glance, the code looks complex, but with a little bit of reading the HX711 datasheet and research of arduino functions is makes sense. The method begins by waiting for the HX711 to be free, in other words for no one else to be reading, though in our case that is not an issue. Following this the function extracts the 24bits of data from the HX711's register, see the [HX711 hardware](#HX711) section for details, and stores it on a buffer. The gain, the channel and percision selection, is reset. And lastly the 24-bit value is translated to a 32-bit variable.

###### Beaglebone
A python script was used to bridge the communication between the arduino and the java web server. The script used a library called PySerial. 
```python
import serial
import requests

ser = serial.Serial('/dev/ttyO2', 9600)

while True:
   dataValue = ser.readline()
   requests.post('http://192.168.7.1/data', data = dataValue)
   
ser.close() 
```

The `serial.Serial('/dev/ttyO2',9600)`call opens the uart2 port (ttyO2) for communication with a baudrate of 9600. `PySerial` itself [will call `os.open()`](https://github.com/pyserial/pyserial/blob/92d101613be41ecb2f2054c3f43a006fbe6f9966/serial/serialposix.py#L265) using the port name which will return a file descriptor, which in this case is a handle to the port. 

[`ser.readline()` from `io::IoBase`](https://docs.python.org/2/library/io.html#io.IOBase.readline) is a standard python method that reads a stream by calling the `IoBase::read()` method until a new line is found. 

The `read()` method is [overriden by `PySerial`](https://github.com/pyserial/pyserial/blob/92d101613be41ecb2f2054c3f43a006fbe6f9966/serial/serialposix.py#L471). The posix version of the `PySerial` code will then call python's `select.select()` method, which [translates to a `select()` system call on linux](https://docs.python.org/2/library/select.html#select.select). This will wait until the port is ready to read and then calls `os.read()` on the serial port to read the data comming from the uart connection. 

`requests.post(..)` is part of the standard python libraries and makes a standard http post request the local java server. 


###### Web Server
A java webserver using the Spring Boot framework is responsible for displaying the values sent by the python server on a web page. 
The webpage uses a chart library (CanvasJS) and websockets in order to constantly update the values. 

The spring boot application enables websocets using `@EnableWebSocketMessageBroker` on the main config class. 

It then registers a web socket entry point using
```java
@Override
public void configureMessageBroker(MessageBrokerRegistry config) {
    config.enableSimpleBroker("/data");
    ...
}
```
That makes it so a client can connect to a websocket using /data/sub.

This can be seen in the javascript code:
```javascript
stompClient.subscribe('/data/sub', function (message){
    var dataToShow = JSON.parse(message.body);
    dps.push({
        x: dataToShow.time,
        y: dataToShow.force
    });
    if (dps.length > dataLength) {
        dps.shift();
    }
    chart.render();
});
```
It subscribes to /data/sub and then pushes a new value to the chart every time a message gets received. 
Every time a value is sent to /data using POST, this method gets triggered: 
```java
@RequestMapping("/data")
public ResponseEntity<String> data(@RequestBody String body) {

    template.convertAndSend("/data/sub", new DataMessage(index.getAndIncrement(), Float.valueOf(body)));

    return ResponseEntity.status(200).build();
}
```

Since only the value is sent in the POST request body, we can convert it directly to a float using `float.valueOf(body)`. 
`template.convertAndSend(...)` will send a websocket message made of an index integer and a float to all the subscribers of the /data/sub websocket. 

#### System Software Communication
The scale has a built in analog to serial conversion (TODO: confirm this), which means the arduino can do a serial read using serial pins. The arduino will then send the number as a string of characters and a new line to the beaglebone using UART (TX/RX pins on both) which nis read by a python script. The beaglebone will take the values and send them over the local network to the computer running the java web server. The connection from the beaglebone to the computer / webserver is done over usb network sharing. The web server will then use the network to send websockets to the clients. 

![communication diagram image](communication_diagram.jpg)

## Development Software

#### Arduino
TODO: Add software / programs used

#### Beaglebone
###### Vim / Nano
Used for code / config editing on the beaglebone. Both were are installed by default on the linux distribution. 

###### Cape manager
Used to add the UART overlay. Installed by default.

###### Python
Used for scriping.

`PySerial` was downloaded using python's pip command, also installed by default. 

#### External
Java was used to run the webserver.

Intellij was used for creating the java web server along with maven for dependency management and packaging. 

Maven dependencies we're all from the spring-boot framework. 

Putty and Ubunutu subsystem for windows were used to shh into the beaglebone.

## System Delivery
#### System Initialisation 
###### Arduino
Flash the main force gauge sketch to the arduio.

###### Beaglebone
**Shell**: `sudo gateway default add 192.168.7.1` and `echo "nameserver 8.8.8.8" > etc/resolv.conf` will enable the beaglebone to use the external computers internet connection. 

**Python**: `sudo pip install PySerial` will install the dependency required for uart communication.

**UART**: In userspace run `sudo sh -c "echo UART2 > /sys/devices/platform/bone_capemgr/slots"` which will add the uart2 tree overlay

###### Windows Computer
**Network**: Enable internet sharing on the proper network adapter (the one connected to the internet). 

**Web Server**: Install a java 8+ jdk [ like the oracle one ](http://www.oracle.com/technetwork/java/javase/downloads/jdk9-downloads-3848520.html). Another option is [openjdk](http://openjdk.java.net/install/index.html).
Install [apache maven](https://maven.apache.org/). In the /website source code directory, run `mvnw clean`, `mvnw validate` and `mvnw package`. This will create a jar in the /target directory that can be run. 

To deploy the web application, in no particular order, start the java server using `java -jar {jar-name}` where the jar name is the jar found in the /target directory and plug in the arduino to the beaglebones power, ground and appropriate uart pins.

Once that is setup, turn on the beaglebone and run the python script by calling `python driver.py`. Once this is done, opening http://127.0.0.1:8080 on the computer/web server should create a webpage with a graph. 

#### System Operation
Once everything is initialized and plugged in, no further interaction is required besides opening the web page previously mentioned. Values should appear on the graph as soon as weight is applied to the scale. 

## Discussion
_TODO_
* internet - wifi setup
* choosing language
* enginneering/machining
* wiring
* communication
* calibrating

###### Web server + application
The python program was meant to send the values using an http POST request to a java webserver, also hosted on the beaglebone. However, the server ended up being hosted an external computer due to a faillure to get newer versions of java working on the beaglebone. 

The library used for websockets is java 8+, however the beaglebone defaults to java 7 when installing using the normal methods. At the time we found out about it, it was too late to change the functionality in order to support java 7. We tried installing java 8 or 9 on the beaglebone but had problems due to what seemed like an incompatible kernel. 

We also had a problem with space management on the beaglebone since their wasn't enough space for the python libraries, the source code, java and all the java dependencies. This was mostly due to a faillure when selecting the web framework since spring-boot is far from lightweight. Looking back, using a handmade c++ or python webserver would have been a better solution. 

## Apendix
#### Figure 1
![proto type](https://user-images.githubusercontent.com/16867443/33049867-0507c6fe-ce30-11e7-84e0-2e0c05b6bfcf.jpg)
#### Figure 2
![concept modle](https://user-images.githubusercontent.com/16867443/33038124-a067f7a6-ce01-11e7-8dc8-f3b6b804d6f7.png)
#### Figure 3
![system](https://user-images.githubusercontent.com/16867443/34211655-ca056dfa-e567-11e7-89f4-f3b61ca5a881.jpg)
#### Figure 4
![calibration](https://user-images.githubusercontent.com/16867443/34211678-dac03db4-e567-11e7-9c89-6a21962e2ef7.jpg)
#### Figure 5
![deformation](https://user-images.githubusercontent.com/16867443/34211718-f7811b1c-e567-11e7-951a-ff1400bf1653.jpg)
