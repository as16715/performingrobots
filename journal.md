# Project Journal 

---

## Week of September 30, 2025  
**Focus:** Motor Control and RC Receiver Pairing

### Hardware Used
* RC Receiver  
* RC Handheld Controller  
* DC Motors  
* Power Supply  

### Objective
To establish reliable communication between the RC controller and RC receiver in order to test basic motor movement and directional control for the robot base.

### Process and Challenges

During this week, the primary focus was connecting and pairing the RC receiver with the handheld RC controller to enable motor movement. We encountered a persistent issue where the RC receiver failed to properly connect. Instead of indicating a successful pairing with a steady green LED, the receiver continuously beeped, signaling that it was unable to bind to the controller.

To troubleshoot this issue, we tried several approaches:
* Moving to a different physical location to avoid interference from other RC controllers
* Rechecking all wiring connections between the receiver, motor controller, and power source
* Power cycling the system multiple times

Despite these efforts, the receiver continued to fail to pair correctly.

### Breakthrough Solution

The issue was ultimately resolved by performing a specific reset sequence on the RC receiver. Using a small screwdriver, we pressed the reset button **three times quickly, followed by two slow presses**, repeating the sequence several times. After this procedure, the receiver LED finally became a steady green, indicating a successful connection to the controller.

This step was critical, as it was not clearly documented in the provided materials and required experimentation and persistence.

### Motor Testing and Control

Once the receiver successfully paired, we moved on to testing motor behavior and modifying the control logic. We mapped:
* The **trigger** on the controller to change direction
* The **scroll wheel** to control forward and backward movement

While this control scheme proved somewhat difficult to manage precisely, it successfully demonstrated that all components were communicating correctly. The robot base was able to move forward, backward, and change direction as intended, confirming that the motor system was functional.

### Media Documentation

[![Motor testing and RC control](https://img.youtube.com/vi/zdoEg5ewHg8/0.jpg)](https://youtube.com/shorts/zdoEg5ewHg8)

---

## Week of October 9, 2025  
**Focus:** Body Structure, Weight Testing, and Early Form Experiments

### Materials and Components Used
* Robot base with motors  
* Long cardboard pipe (body foundation)  
* L-brackets  
* Screws and fasteners  
* Bamboo sticks  
* Cling film  
* Hot glue  
* Balloon  

### Objective
To establish a lightweight structural foundation for the robot body and test how additional vertical mass would affect balance, mobility, and drivability of the robot base.

### Structural Decisions and Assembly

This week, we found a long cardboard pipe that we decided to use as the main structural element for the robot’s body. Instead of using heavier materials such as wooden planks, we chose the cardboard pipe as a lightweight alternative that would allow us to build vertically without immediately overloading the small motorized base.

The pipe was attached to the base using L-brackets, securely screwed into place. This allowed the structure to stand upright while remaining modular enough to adjust or remove later if needed.

### Movement and Weight Testing

After mounting the pipe, we conducted movement tests to evaluate whether the added structure affected the robot’s ability to drive, turn, or balance. The results were surprisingly positive. The cardboard pipe added minimal weight and did not significantly interfere with the base’s mobility or control.

Choosing a lightweight material early on felt important, as we anticipated the body becoming heavier later in the semester with additional components. By keeping the initial structure light, we aimed to prevent balancing issues and motor strain in future iterations.

### Media Documentation

[![Base movement test with cardboard pipe](https://img.youtube.com/vi/Y9p4qHg4FWY/0.jpg)](https://youtube.com/shorts/Y9p4qHg4FWY)

### Early Body and Head Prototyping

In addition to testing the body foundation, we began experimenting with constructing a head and torso using unconventional materials. We cut holes into the cardboard pipe and inserted bamboo sticks in a criss-cross arrangement to serve as attachment points.

For the head, we inflated a balloon, wrapped it completely in cling film, and then traced a grid pattern over the surface using hot glue. This process gave the form structure and rigidity. Once the glue dried, we popped the balloon, leaving behind a lightweight, hollow head shape.

To create the body form, we used a similar method by wrapping cling film around my own body, cutting it off, and reinforcing it with hot glue. This resulted in a human-scale shell that suggested a performative, sculptural presence rather than a purely mechanical one.

These components were set aside for later integration, as we planned to design more secure attachment methods to connect the head and body forms to the central pipe structure.

### Reflection

This week marked a shift from purely mechanical testing toward thinking about the robot's appearance. The use of lightweight, flexible materials allowed us to explore form without sacrificing mobility.

---

## Week of November 11, 2025 

## Hardware Used

* Arduino Uno (Transmitter)
* Arduino Mega (Receiver)
* nRF24L01 Wireless Modules (x2)
* 16x2 LCD Display
* Push Buttons (5 total)

## Objective

To establish wireless communication between two Arduinos using the nRF24L01 modules, with one functioning as a transmitter and the other as a receiver, following the instructor’s provided documentation.

## Progress Summary

### Initial Setup

Both the transmitter and receiver were configured according to the assignment instructions. The shared `.ino` file was modified by uncommenting the relevant sections marked with `CHANGEHERE` to switch between transmitter and receiver modes.

### Receiver Configuration

The receiver code was uploaded to the Arduino Mega. After adjusting CE and CSN pin definitions, the receiver successfully initialized the radio and began listening for incoming packets.

### Transmitter Configuration

The transmitter was uploaded to the Arduino Uno, with CE and CSN pins defined on A4 and A5, respectively. The LCD displayed “I am a transmitter” after successful initialization.

## Images

![LCD Display 1](/images/lcd1.jpg)

![LCD Display 2](/images/lcd2.jpg)


