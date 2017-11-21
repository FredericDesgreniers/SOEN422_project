# Project Proposal

### Table of Contents
1. [Contributors](#Contributors)
2. [Concept](#Concept)
3. [Systems](#Systems)
4. [Extra Hardware Requirements](#Extra-Hardware-Requirements)

## Contributors - Team Cerberus
**Name** | **ID**
:--:|---
Christopher McArthur | `40004257`
Frederic Desgreniers | `40016777`

## Concept
Having spent several years as an amature kickboxer, one question that has always came up in the gym is

> How much force am I hitting with?

The challenge with this is that technical skills required for building the correct test gauge are not common in the community nor are the funds to by fancy equipement. That however is longer not the case. When I was a teenager there was a show sports science which done [episodes](https://www.youtube.com/watch?v=-iLno2uSRXg) of this and fulled my curiosity. The basic idea because this will be to build a system which will be able to accurately detect the force applied from a punch or kick and display it on a monitor. I specialize in network applications so I would be most comftorable using my costume IP for the communication between the Arduino and Begalbone. In line with this would most likely be a web UI for view the results of each test.

## Systems
I would like to build two systems, though in-depth design will be needed to establish which is less fesable.

- Boxing: _Force plate_ - This will be a flat plate for test subjects to punch and will work much like a scale. The difficulty will lie in the engineering of the device. It will be required to hang vertiacally making it difficult to use many of the cheaper types of load cells as attaching the front plate correctly becomes a concern.
- Kickboxing: _Bag gauge_ - This would eliminat much of the engineering difficults of mounting the load cells but would require a higher rated cell because the force behind a pick is much greater. The biggest difficulty will be place the device correctly to capture the force without it being diminised by the bag swing.

## Extra Hardware Requirements
* [HX711](https://www.sparkfun.com/products/13879) < $10
* 4 x [Load Cell 50kg](http://www.robotshop.com/ca/en/micro-load-cell-50-kg.html) < $10 each
* [Combinator Board](https://www.sparkfun.com/products/13878) < 2$
* Wifi dongle for the Begalbone Black

