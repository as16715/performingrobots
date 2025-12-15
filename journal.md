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

## Week of October 24, 2025  
**Focus:** Head Attachment Mechanism and Servo Integration

### Materials and Components Used
* Servo motor  
* Servo brackets and horn  
* SparkFun kit wheel  
* Plywood (cut into circular plates)  
* Bamboo sticks (existing internal structure)  
* Zip ties  
* Screws and fasteners  

### Objective
To design and implement a reliable mechanism for attaching and rotating the robot’s lightweight head while keeping internal electronics protected and accessible.

### Head Attachment Planning

At the start of the week, we explored using a lazy Susan bearing as a way to mount and rotate the robot’s head. While this approach would have worked mechanically, it depended on finding a bearing small enough to match the scale of our robot’s head, which introduced delays.

During a check-in, the professor suggested a simpler and more effective alternative: since the head was extremely lightweight, it did not require a heavy-duty bearing system. Instead, a small wheel from a SparkFun kit could be used as the rotating interface, driven directly by a servo motor. This solution was better aligned with the scale and materiality of the robot.

### Servo and Structural Integration

To mount the servo motor securely inside the cardboard pipe, we laser cut circular plywood plates with a diameter matching the interior of the pipe. The servo motor was attached to one of these plywood circles using servo brackets, creating a stable motor mount.

Rather than permanently fixing the plywood mount to the pipe, we took advantage of the bamboo sticks that had already been installed inside the pipe. Two holes were drilled into the plywood circle, and zip ties were routed through these holes and around the bamboo sticks. This allowed us to anchor the motor mount firmly in place while keeping it removable and adjustable.

This configuration also had the added benefit of creating a clean internal cover for the electronics, keeping wiring organized and out of sight while still allowing the servo motor to operate smoothly.

### Head Installation

The SparkFun wheel was attached to the servo motor using a standard servo horn. The head was then screwed directly onto the wheel. To ensure the head stayed firmly pressed against the wheel and did not wobble during movement, we added a smaller plywood circle on the opposite side, functioning like a washer to distribute pressure evenly.

This assembly resulted in a stable, lightweight head attachment that could rotate cleanly without placing unnecessary strain on the motor.

### Reflection

This week highlighted the value of choosing solutions that match the scale and material constraints of the project. By opting for a lightweight wheel instead of a more complex bearing system, we were able to simplify the design and maintain a clean internal structure. The modular mounting approach would also make future adjustments easier as the robot continued to evolve.

---

## Week of October 30, 2025  
**Focus:** Body Attachment, Structural Shoulder, and Arm Motor Mounting

### Materials and Components Used
* Cardboard pipe (body structure)  
* Bamboo sticks  
* Wooden board (custom cut)  
* Arduino (secondary controller)  
* Servo motors  
* Servo brackets  
* M6 50mm nuts and bolts  
* Screws and fasteners  

### Objective
To securely attach the robot’s body to the central pipe structure while creating a stable “shoulder” platform capable of supporting electronics and arm movement mechanisms.

### Body Attachment Strategy

To attach the cling film body form to the pipe, we first extended several long bamboo sticks through the pipe horizontally. These sticks acted as support beams for the body shell to rest on, allowing the lightweight cling film corset structure to balance and sit naturally around the pipe without collapsing.

This approach allowed the body to remain visually integrated with the structure while avoiding the need for adhesives or permanent attachment, keeping the system modular.

### Shoulder Structure Fabrication

To create a more rigid structural element for both electronics and arm movement, we cut two rectangular openings into the cardboard pipe. Through these openings, we planned to insert a wooden piece that would function as the robot’s shoulder platform.

The wooden piece was cut in the scene shop using a bandsaw, carefully sized to match the internal diameter of the pipe. Additional cuts were made to ensure the piece could accommodate an Arduino board mounted on top.

Once prepared, the wooden platform was routed through the top of the pipe and positioned so that it rested securely within the rectangular cutouts, forming a horizontal shoulder inside the pipe.

### Electronics and Motor Mounting

A second Arduino was mounted directly onto the wooden shoulder platform, creating a centralized and stable location for control hardware. To lock the wooden piece firmly in place, we used two long M6 50mm nuts and bolts, inserting them through the wood on either side of the pipe. These bolts acted as mechanical stoppers, preventing the platform from shifting or sliding out of position.

Servo brackets were then attached to both sides of the wooden platform, and servo motors were mounted onto these brackets. These servos were intended to drive the robot’s arms, making this the first week where arm movement was structurally planned and physically supported.

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

---

## Week of November 18, 2025  
**Focus:** Wireless Transmitter Integration and Arm Construction

### Materials and Components Used
* nRF24 transmitter setup  
* Arduino (transmitter)  
* Servo motors (25kg)  
* Bamboo sticks  
* Servo horns  
* Zip ties  
* Screws and fasteners  
* Glue  

### Objective
To establish wireless control over at least one expressive movement of the robot while continuing the construction and refinement of the robot’s arms.

### Transmitter Development

This week marked a major step forward in wireless control. My partner focused primarily on setting up and debugging the transmitter, successfully getting it to communicate with the robot and trigger movement. The first movement we implemented through the transmitter was head rotation.

After configuring the transmitter, we tested whether the head servo could be reliably controlled using case-based inputs. The test was successful, confirming that the wireless system could activate specific behaviors rather than just raw motor movement. This was an important milestone, as it validated our approach to remote performance control.

### Media Documentation

![Partner working on transmitter setup](/images/transmit.jpeg)

### Arm Design and Construction

While the transmitter work was underway, I focused on constructing the robot’s arms. Continuing our strategy of keeping the robot as lightweight as possible, I chose bamboo sticks as the primary arm material. The arms were designed with the understanding that the robot would be wearing a black cloak as part of its judge character, meaning the visual appearance of the arms themselves was less critical than their function.

I carefully drilled holes into long, thin bamboo sticks and planned to later wrap them with pool noodles for volume if needed. The arms were initially screwed directly onto the shoulder servos, but this approach proved unstable, as the bamboo began to loosen over time.

To correct this, I reattached the arms using proper servo horns, securing the bamboo to the horn first and then mounting the horn onto the servo. To prevent the bamboo from splitting during movement, I reinforced the attachment point with tightly wrapped zip ties.

### Servo Selection and Arm Functionality

Because the bamboo arms were extremely lightweight, we opted to use 25kg servos rather than heavier-duty motors. These provided more than enough torque without adding unnecessary weight to the structure.

Each arm was designed with a specific performative role in mind:
* One arm was intended to hold a gavel  
* The other was designed to hold a cigar  

The cigar arm needed to bend inward toward the robot’s mouth. To achieve this, I cut one bamboo arm into two sections and reattached them at an elbow angle. The joint was reinforced using glue and multiple zip ties, creating a stable bend that functioned reliably during movement tests.

### Reflection

This week highlighted the importance of parallel workflows and clear division of labor. While the transmitter work enabled remote control of expressive behaviors, the arm construction focused on material efficiency and character-driven design. The success of the bent bamboo arm demonstrated that simple, low-cost materials could still produce effective performative gestures.




