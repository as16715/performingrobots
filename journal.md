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

---

## Week of November 24, 2025  
**Focus:** Arm Artifacts, Lighting Experiments, Audio Integration, and Base Motor Debugging

### Materials and Components Used
* Bamboo arm structures  
* Small circular pipe (cigar prop)  
* NeoPixel LEDs (ring and single)  
* Halloween mask  
* Hot glue (used as diffuser)  
* LED strip lights  
* Music Maker Shield  
* Arduino  
* H-bridge motor driver  
* Soldering tools and wiring  

### Objective
To develop expressive artifacts for the robot’s arms, experiment with lighting and audio electronics, and troubleshoot persistent issues with the robot’s base motors.

### Arm Artifacts and Props

This week, I focused on building the physical artifacts that would enhance the robot’s performative gestures. I began with the cigar prop for the cigar arm. A small, circular makeshift pipe was glued directly onto the bamboo arm to represent the cigar. This provided a simple but readable prop that aligned with the character of the robot.

While I worked on the physical artifacts, my partner focused on developing and refining the transmitter cases according to the performance script.

### Lighting and Head Electronics

I then moved on to adding lighting elements to the robot’s head. I soldered circular NeoPixel LEDs and mounted them behind the eye cutouts of a Halloween mask. To soften and diffuse the light, I created small slabs of hot glue that acted as a diffuser in front of the LEDs.

I also experimented with placing LED strip lights inside the head itself. However, due to the multiple layers of cling film and hot glue used to construct the head, the internal lighting was not very visible from the outside. In contrast, the NeoPixels mounted directly on the mask worked extremely well, maintaining brightness and clarity.

One advantage of this approach was modularity: once the wiring was completed, the mask could simply be popped onto the head, allowing for easy installation and removal.

In addition, I attached a single NeoPixel to the cigar prop, with the intention of creating a bright orange animation to visually indicate when the robot was “using” the cigar.

### Audio Integration

Later in the week, we attached a Music Maker Shield to the Arduino to incorporate sound into the robot’s performance. My partner initially ran into issues configuring the shield, but the problem was ultimately traced back to code and library conflicts rather than hardware. Once the correct libraries were installed and referenced, the shield began functioning as expected.

### Base Motor Troubleshooting

I also returned to debugging the robot’s base motors, as driving the robot had become increasingly difficult—particularly when attempting to turn left. To diagnose the issue, I propped the robot up on blocks of wood so the wheels could spin freely while being observed.

Through this test, I noticed that one motor was able to move forward but not backward. I first verified that this was not a software issue by reviewing the motor control code. Next, I swapped the M1 and M2 motor connections on the H-bridge. After swapping, the issue followed the channel rather than the motor: the other wheel now exhibited the same one-directional behavior.

This ruled out a faulty motor and suggested that the H-bridge itself might be malfunctioning. We replaced the H-bridge later in the week, but the issue unfortunately persisted, indicating a deeper problem that would require further investigation.

---

## Week of Novemebr 30, 2025  
**Focus:** Motor Debugging, Movement Refinement, and Audio Production

### Materials and Components Used
* Robot base and motor system  
* Motor shield  
* Arduino  
* Audio files (generated and edited)  
* Audacity  
* Hume AI  

### Objective
To resolve persistent motor issues, refine the robot’s driving behavior for performance safety, and finalize audio assets for the judge character.

### Motor Repair and Diagnosis

Over the weekend, the professor helped us diagnose the ongoing motor issues. After inspecting the motor shield, he identified and repaired some poor solder joints. Once these joints were fixed, the motors immediately began functioning reliably again, confirming that the issue was hardware-related rather than code-based.

With the motor system restored, I resumed work on the movement code while my partner focused on finalizing all transmitter cases for the performance.

### Control Mapping and Movement Refinement

I began by remapping the motor controls to make driving more intuitive. The trigger was assigned to forward movement, while the wheel input was used for turning left and right. This change significantly improved usability during rehearsals.

However, rehearsals revealed another major issue: because the robot was tall and mounted on a relatively small base, it had a strong tendency to tip over. This problem was amplified by the motors being too fast and stopping too abruptly.

During testing, I observed that the two base motors did not behave identically, even when receiving the same control values. One motor would begin moving at a lower input value, while the other would stall until a higher value was reached. This revealed a difference in the motors’ **minimum effective PWM threshold**—the minimum pulse-width modulation value required for each motor to overcome static friction and begin rotating.

### Motor Calibration and Stability Improvements

To address this, I repeatedly tested and adjusted the threshold values for each motor so they would start moving at the same time and operate at matching speeds. Once calibrated, I significantly reduced the overall motor speed to improve stability and reduce the risk of tipping.

I also implemented a smooth stop function so the robot would decelerate gradually instead of stopping abruptly. Over the course of multiple rehearsals, I further reduced turning speed, as sharp turns were another major cause of instability.

Ultimately, the motors were slowed to the lowest viable speed that still allowed reliable movement without stalling. While this made the robot considerably slower, it greatly improved control accuracy and performance safety.

### Audio Production and Integration

In parallel with motor tuning, I worked on generating and refining the judge’s voice lines. I used Hume AI to generate each line of dialogue, then manually edited the recordings in Audacity to adjust tone, timing, and character expression.

To simplify performance control, I embedded scene-specific sound cues—such as gavel bangs and typing sounds—directly into the voice tracks themselves. This reduced the need to trigger additional sounds manually during performance.

Each audio file was numbered according to scene order, making it easy to integrate them chronologically into the transmitter cases. All finalized audio assets were uploaded to GitHub for organization and version control.


---

## Week of December 4, 2025  
**Focus:** Costuming, Audio Debugging, Structural Reinforcement, and Final Polish

### Materials and Components Used
* Costume pieces (dress, hair, cloak)  
* Music Maker Shield  
* Speaker and SD card  
* Pool noodles  
* Paper stuffing  
* Wooden planks  
* Casters  
* Cardboard spacers  
* Metal servo horn  
* Aluminum sheet  
* Skewers  
* Glue, screws, brackets  

### Objective
To integrate costuming, resolve remaining audio issues, reinforce fragile mechanical systems, and prepare the robot for final performance conditions.

### Costuming and Visual Integration

This week began with checking out the robot’s costume elements, including hair and a dress for the body. To dress the robot, I carefully undid sections of the internal wiring so the costume could be slipped on cleanly. Once dressed, the wiring was rerouted and secured, and the hair was pinned into place on the head.

### Media Documentation

[![Costumes and visual setup](https://img.youtube.com/vi/gXhM2jlB3BE/0.jpg)](https://youtube.com/shorts/gXhM2jlB3BE)

### Case Finalization and Audio Issues

By this point, all transmitter cases were functionally complete, requiring only minor calibrations. However, we encountered a major issue with the robot’s audio: the sound quality was extremely poor and full of static.

We systematically diagnosed the problem:
* Reviewed the code for errors  
* Checked whether the audio files on the SD card were corrupted  
* Replaced the speaker battery  
* Swapped the Music Maker Shield  

None of these steps resolved the issue. Eventually, we realized that all audio files were in `.wav` format, which I had used because Audacity primarily works with WAV files. As an experiment, I converted one file to `.mp3`, and the audio played back perfectly.

After this discovery, I converted all sound files to MP3 format and re-uploaded them to the SD card, which completely resolved the audio quality issue.

### Body Decoration and Head Stabilization

With audio resolved, I moved on to decorating the robot’s body. Pool noodles were attached to the bamboo arms to add volume, and the cigar and a makeshift gavel were glued into place. The head and body were stuffed with paper to make the forms more rigid.

This introduced a new issue: the head had a strong tendency to tip forward during movement. I initially attempted to counterbalance it by attaching small weights to the back of the head using fishing wire hidden in the hair, but this had minimal effect.

To properly solve the issue, I removed the stuffing and inserted two skewers through the base of the head, routing them into existing holes in the wheel the head was mounted on. After reinserting the stuffing, these internal supports kept the head upright at all times without adding extra weight.

### Background Slides and Rehearsal Accident

I also worked on creating background slides for the performance, particularly for the scene where the judge and best friend text each other through their partners’ phones.

During a rehearsal this week, we experienced a significant collision when the husband robot crashed into our robot, causing it to tip over. One of the arms broke in the impact. Fortunately, the bamboo arm itself remained intact; the failure occurred at the plastic servo horn, which split in half.

### Stability Improvements and Castor Addition

To prevent future tipping and collisions, I reinforced the broken arm using a metal servo horn and decided to add an additional set of castors to the base.

Because the robot’s base was most prone to tipping at approximately 45° and 135°, I cut two narrow wooden planks in the scene shop, carefully sized to fit underneath the base without interfering with existing screws. Casters were mounted onto these planks using brackets, with five layers of cardboard added between the bracket and plank to lower the caster height slightly.

The goal was for the added castors to hover about half a centimeter above the ground—only engaging when the robot began to tip, rather than remaining in constant contact.

![Additional stabilizing castors](/images/castor.jpg)

### Arm Repair and Reinforcement

To repair the broken arm, I removed the damaged plastic horn and fabricated a replacement using a thin aluminum sheet. I cut a square piece, drilled holes matching both the servo mounting pattern and the existing holes in the bamboo arm, and secured the arm to the aluminum plate and the plate to the servo.

This created a much stronger attachment point that was far less likely to fail under sudden stress.

![Reinforced arm attachment](/images/arm.jpg)

### Final Preparations

In the days leading up to the final performance, I painted the remaining artifacts while my partner refined the cases, integrating multitasking behaviors and small performance details. Finally, we borrowed a black cloak and used it to hide all exposed wiring and electronics, completing the robot’s visual transformation.

### Reflection

This week emphasized the realities of preparing a robot for live performance. Many systems that worked independently had to be reinforced, simplified, or rethought once rehearsals introduced unpredictability. By addressing audio quality, stability, and durability, the robot became significantly more reliable and visually cohesive going into the final performance.

---

## Final Performance Reflection  

Looking back at this semester, I have so many thoughts swirling around. I think my biggest regret is not taking more pictures—both of the final robot and throughout the entire process. Sometimes the little wins at the end of each week would have felt so much bigger if I had documented them properly. Instead, a lot of the memories live in my head, which is fine, but having a visual record would have been something special.  

I’ve wanted to take this class since sophomore year when I first switched my major to IM, and finally getting into it in my senior year has been such a blessing. Even though I do wish I had done more, I am incredibly proud of what we accomplished. There are little things I wish I could have added—like the cigar mist for the robot—that didn’t make it to the final version. I remember being so ready for this project at the start: I even found my old diffuser and unscrewed all its electronics to see if I could attach it to the robot. In hindsight, it would have needed more planning—like where to store the water or how to make the mist visible—but just that initial curiosity and excitement reminded me how much I love building things.  

I’m genuinely happy with where we ended. This project threw countless challenges our way—mechanical issues, code bugs, unexpected failures—but each one taught me something. As much as I tried to anticipate problems, there were always new surprises. And yet, the planning, debugging, and thought process we put in really did make a difference. They eased a lot of potential headaches and helped us keep moving forward, week by week.  

Looking back, some of my favorite moments weren’t the big “goal achieved” milestones, but the small victories—the first time the head moved without tipping, finally getting the NeoPixels to work, or just seeing the robot dressed and performing a single motion correctly. Those moments reminded me why I wanted to take this class in the first place: to create something alive, something that moves, reacts, and tells a story.  

All in all, this class has been a perfect combination of frustration, excitement, and joy. I learned so much—not just about robots, code, and electronics, but also about patience, persistence, and the thrill of seeing an idea come to life. Even the challenges now feel like part of the story, part of the process that made the final performance feel earned and meaningful.  

I’m grateful for this experience, for the guidance of the professor, for my partner’s collaboration, and for the chance to finally bring this robot to life. It’s been messy, it’s been tricky, but it’s also been one of the most rewarding projects I’ve ever done. And despite the things I wish I could have done differently, I wouldn’t change the feeling of building it, week by week, from nothing to a fully performative robot.  

![Final performance reflection](/images/reflection.jpg)




