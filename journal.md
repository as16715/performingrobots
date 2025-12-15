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


**Date:** 11/6/2025

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


