// Sudiksha & Aysha
// Professor Micheal Shiloh
// Performing Robots Fall '25

/*
   Using the nRF24L01 radio module to communicate
   between two Arduinos with much increased reliability following
   various tutorials, conversations, and studying the nRF24L01 datasheet
   and the library reference.

   Transmitter is
   https://github.com/michaelshiloh/resourcesForClasses/tree/master/kicad/Arduino_Shield_RC_Controller

  Receiver is
  https://github.com/michaelshiloh/resourcesForClasses/blob/master/kicad/nRF_servo_Mega

   This file contains code for both transmitter and receiver.
   Transmitter at the top, receiver at the bottom.
   One of them is commented out, so you need to comment in or out
   the correct section. You don't need to make changes to this
   part of the code, just to comment in or out depending on
   whether you are programming your transmitter or receiver

   You need to set the correct address for your robot.

   Search for the phrase CHANGEHERE to see where to
   comment or uncomment or make changes.

   These sketches require the RF24 library by TMRh20
   Documentation here: https://nrf24.github.io/RF24/index.html

   change log

   11 Oct 2023 - ms - initial entry based on
                  rf24PerformingRobotsTemplate
   26 Oct 2023 - ms - revised for new board: nRF_Servo_Mega rev 2
   28 Oct 2023 - ms - add demo of NeoMatrix, servo, and Music Maker Shield
   20 Nov 2023 - as - fixed the bug which allowed counting beyond the limits
   22 Nov 2023 - ms - display radio custom address byte and channel
   12 Nov 2024 - ms - changed names for channel and address allocation for Fall 2024
                      https://github.com/michaelshiloh/resourcesForClasses/blob/master/kicad/nRF_servo_Mega
                      https://github.com/michaelshiloh/resourcesForClasses/blob/master/kicad/nRFControlPanel

   [USER] Nov 2025 - Custom choreography for gavel, head, and cigar robot
                     with servo + NeoPixel helpers mapped to M1–M6.
*/

// Common code
//

// Common pin usage
// Note there are additional pins unique to transmitter or receiver
//

// nRF24L01 uses SPI which is fixed
// on pins 11, 12, and 13 on the Uno
// and on pins 50, 51, and 52 on the Mega

// It also requires two other signals
// (CE = Chip Enable, CSN = Chip Select Not)
// Which can be any pins:

// CHANGEHERE
// For the transmitter
const int NRF_CE_PIN = A4, NRF_CSN_PIN = A5;

// CHANGEHERE
// for the receiver
// const int NRF_CE_PIN = A11, NRF_CSN_PIN = A15;

// nRF 24L01 pin   name
//          1      GND
//          2      3.3V
//          3      CE
//          4      CSN
//          5      SCLK
//          6      MOSI/COPI
//          7      MISO/CIPO

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(NRF_CE_PIN, NRF_CSN_PIN); // CE, CSN

// #include <printf.h>  // for debugging

// See note in rf24Handshaking about address selection
//

// Channel and address allocation:
// Rama and Hind Y: Channel 30, addr = 0x76
// Ahsen and Pranav: Channel 40, addr = 0x73
// Sara & Toomie:  Channel 50, addr = 0x7C
// Avinash and Vahagn: Channel 60, addr = 0xC6
// Hind A & Javeria:  Channel 70, addr = 0xC3
// Mbebo and Aaron: Channel 80, addr = 0xCC
// Linh and Luke: Channel 90, addr = 0x33

// CHANGEHERE
const byte CUSTOM_ADDRESS_BYTE = 0x73; // change as per the above assignment
const int CUSTOM_CHANNEL_NUMBER = 40;  // change as per the above assignment

// Do not make changes here
const byte xmtrAddress[] = {CUSTOM_ADDRESS_BYTE, CUSTOM_ADDRESS_BYTE, 0xC7, 0xE6, 0xCC};
const byte rcvrAddress[] = {CUSTOM_ADDRESS_BYTE, CUSTOM_ADDRESS_BYTE, 0xC7, 0xE6, 0x66};

const int RF24_POWER_LEVEL = RF24_PA_LOW;

// global variables
uint8_t pipeNum;
unsigned int totalTransmitFailures = 0;

struct DataStruct
{
  uint8_t stateNumber;
};
DataStruct data;

// *** MODIFICATION: Add a "busy" flag for the transmitter ***
bool isTransmitting = false;

void setupRF24Common()
{
  // RF24 setup
  if (!radio.begin())
  {
    Serial.println(F("radio  initialization failed"));
    while (1)
      ;
  }
  else
  {
    Serial.println(F("radio successfully initialized"));
  }

  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(CUSTOM_CHANNEL_NUMBER);
  radio.setPALevel(RF24_POWER_LEVEL);
}

// CHANGEHERE

// Transmitter code

// Transmitter pin usage
const int LCD_RS_PIN = 3, LCD_EN_PIN = 2, LCD_D4_PIN = 4, LCD_D5_PIN = 5, LCD_D6_PIN = 6, LCD_D7_PIN = 7;
const int SW1_PIN = 8, SW2_PIN = 9, SW3_PIN = 10, SW4_PIN = A3, SW5_PIN = A2;

// LCD library code
#include <LiquidCrystal.h>

// initialize the library with the relevant pins
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

// MEERA EDIT
const int NUM_OF_STATES = 32;
char *theStates[] = {
    // Scene 1 (Track 1)
    "Scene 1.1",
    // Scene 3 (Tracks 2–12)
    "Scene 4.1",
    "Scene 4.2",
    "Scene 4.3",
    "Scene 4.4",
    "Scene 4.5",
    "Scene 4.6",
    "Scene 4.7",
    "Scene 4.8",
    "Scene 4.9",
    "Scene 4.10",
    "Scene 4.11",
    // Scene 5 (Tracks 13–20)
    "Scene 5.1",
    "Scene 5.2",
    "Scene 5.3",
    "Scene 5.4",
    "Scene 5.5",
    "Scene 5.6",
    "Scene 5.7",
    "Scene 5.8"};

void updateLCD()
{
  lcd.clear();
  lcd.print(theStates[data.stateNumber]);
  lcd.setCursor(0, 1); // column, line (from 0)
  lcd.print("not transmitted yet");
}

void countDown()
{
  data.stateNumber = (data.stateNumber > 0) ? (data.stateNumber - 1) : 0;
  updateLCD();
}

void countUp()
{
  if (++data.stateNumber >= NUM_OF_STATES)
  {
    data.stateNumber = NUM_OF_STATES - 1;
  }
  updateLCD();
}
void spare1() {}
void spare2() {}

void rf24SendData()
{

  // // *** MODIFICATION: Prevent re-entry if already transmitting ***
  // if (isTransmitting) {
  //   Serial.println(F("Already transmitting, please wait."));
  //   // We can even tell the user on the LCD
  //   lcd.setCursor(0, 1);
  //   lcd.print("Busy...         ");
  //   return; // Exit the function immediately
  // }
  // isTransmitting = true; // Set the flag so we can't run again

  radio.stopListening(); // go into transmit mode
  // The write() function will block
  // until the message is successfully acknowledged by the receiver
  // or the timeout/retransmit maxima are reached.
  int retval = radio.write(&data, sizeof(data));

  lcd.clear();
  lcd.setCursor(0, 0); // column, line (from 0)
  lcd.print("transmitting");
  lcd.setCursor(14, 0); // column, line (from 0)
  lcd.print(data.stateNumber);

  Serial.print(F(" ... "));
  if (retval)
  {
    Serial.println(F("success"));
    lcd.setCursor(0, 1); // column, line (from 0)
    lcd.print("success");
  }
  else
  {
    totalTransmitFailures++;
    Serial.print(F("failure, total failures = "));
    Serial.println(totalTransmitFailures);

    lcd.setCursor(0, 1); // column, line (from 0)
    lcd.print("error, total=");
    lcd.setCursor(13, 1); // column, line (from 0)
    lcd.print(totalTransmitFailures);
  }

  // *** MODIFICATION: Clear the "busy" flag when done ***
  // isTransmitting = false;
}

class Button
{
  int pinNumber;
  bool previousState;
  void (*buttonFunction)();

public:
  // Constructor
  Button(int pn, void *bf)
  {
    pinNumber = pn;
    buttonFunction = bf;
    previousState = 1;
  }

  // update the button
  void update()
  {
    bool currentState = digitalRead(pinNumber);
    if (currentState == LOW && previousState == HIGH)
    {
      Serial.print("button on pin ");
      Serial.print(pinNumber);
      Serial.println();
      buttonFunction();
    }
    previousState = currentState;
  }
};

const int NUMBUTTONS = 5;
Button theButtons[] = {
    Button(SW1_PIN, countDown),
    Button(SW2_PIN, rf24SendData),
    Button(SW3_PIN, countUp),
    Button(SW4_PIN, spare1),
    Button(SW5_PIN, spare2),
};

void setupRF24()
{
  setupRF24Common();

  // Set us as a transmitter
  radio.openWritingPipe(xmtrAddress);
  radio.openReadingPipe(1, rcvrAddress);

  // radio.printPrettyDetails();
  Serial.println(F("I am a transmitter"));
  data.stateNumber = 0;
}

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Setting up LCD"));

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  // Print a message to the LCD.
  lcd.print("Radio setup");

  // Display the address in hex
  lcd.setCursor(0, 1);
  lcd.print("addr 0x");
  lcd.setCursor(7, 1);
  char s[5];
  sprintf(s, "%02x", CUSTOM_ADDRESS_BYTE);
  lcd.print(s);

  // Display the channel number
  lcd.setCursor(10, 1);
  lcd.print("ch");
  lcd.setCursor(13, 1);
  lcd.print(CUSTOM_CHANNEL_NUMBER);

  Serial.println(F("Setting up radio"));
  setupRF24();

  // If setupRF24 returned then the radio is set up
  lcd.setCursor(0, 0);
  lcd.print("Radio OK state=");
  lcd.print(theStates[data.stateNumber]);

  // Initialize the switches
  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(SW2_PIN, INPUT_PULLUP);
  pinMode(SW3_PIN, INPUT_PULLUP);
  pinMode(SW4_PIN, INPUT_PULLUP);
  pinMode(SW5_PIN, INPUT_PULLUP);
}

void loop()
{
  for (int i = 0; i < NUMBUTTONS; i++)
  {
    theButtons[i].update();
  }
  delay(50); // for testing
}

void clearData()
{
  // set all fields to 0
  data.stateNumber = 0;
}

// End of transmitter code
// CHANGEHERE

// Receiver Code
// CHANGEHERE
/*
// Uncomment this to activate the receiver code

// Additional libraries for music maker shield
#include <Adafruit_VS1053.h>
#include <SD.h>

// Servo library
#include <Servo.h>

// NeoPixel strip for HEAD NEOPIXELS + CIGAR NEOPIXEL
#include <Adafruit_NeoPixel.h>

// ===== Music Maker Shield pins =====
#define SHIELD_RESET -1  // VS1053 reset pin (unused!)
#define SHIELD_CS 7      // VS1053 chip select pin (output)
#define SHIELD_DCS 6     // VS1053 Data/command select pin (output)
#define CARDCS 4         // SD card chip select pin
#define DREQ 3           // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(
  SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

// Connectors for NeoPixels and Servo Motors are labeled
// M1 - M6 with these pin assignments on nRF_Servo_Mega:
// M1 = 19
// M2 = 20
// M3 = 21
// M4 = 16
// M5 = 18
// M6 = 17
//
// Your mapping:
// M6 head servo
// M5 gavel servo
// M3 cigar servo
// M1 cigar NeoPixel
// M2 head NeoPixels

// ===== Servo pins =====
const int GAVEL_SERVO_PIN = 18;  // M5: gavel
const int CIGAR_SERVO_PIN = 21;  // M3: cigar
const int HEAD_SERVO_PIN  = 17;  // M6: head

Servo gavel;
Servo cigar;
Servo head;

// Gavel angles
const int GAVEL_REST_ANGLE = 60;   // up / neutral
const int GAVEL_BANG_ANGLE = 120;  // down on table

// Cigar angles
const int CIGAR_DOWN_ANGLE = 110;  // lowered, not smoking
const int CIGAR_UP_ANGLE   = 40;   // up near mouth

// Head angles (tune in rehearsal)
const int HEAD_CENTER_ANGLE       = 90;   // facing front
const int HEAD_TOWARD_WIFE_ANGLE  = 135;  // turn right
const int HEAD_TOWARD_CHILD_ANGLE = 45;   // turn left
const int HEAD_AWAY_ANGLE         = 30;   // look away left

// ===== NeoPixel configuration =====
// Head NeoPixels on M2, cigar NeoPixel on M1.
const int HEAD_NEOPIXEL_PIN  = 20;  // M2
const int CIGAR_NEOPIXEL_PIN = 19;  // M1

const uint8_t HEAD_LED_COUNT = 31;  // adjust to your actual head LED count

Adafruit_NeoPixel headStrip = Adafruit_NeoPixel(
  HEAD_LED_COUNT, HEAD_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel cigarStrip = Adafruit_NeoPixel(
  1, CIGAR_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// ----- Small helpers for colors and simple actions -----

// Map logical RGB to GRB order used by the strips, so calling code can
// think in normal (R,G,B) space.
uint32_t headColorRGB(uint8_t r, uint8_t g, uint8_t b) {
  return headStrip.Color(g, r, b);
}

uint32_t cigarColorRGB(uint8_t r, uint8_t g, uint8_t b) {
  return cigarStrip.Color(g, r, b);
}

// Standard rainbow wheel for head ring.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return headColorRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return headColorRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return headColorRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// ----- HEAD NEOPIXELS (mood) -----

void headSetColor(uint8_t r, uint8_t g, uint8_t b) {
  for (uint8_t i = 0; i < HEAD_LED_COUNT; i++) {
    headStrip.setPixelColor(i, headColorRGB(r, g, b));
  }
  headStrip.show();
}

// semantic wrappers
void headSetDefault() { headSetColor(255, 255, 255); }  // white = default
void headSetRed()     { headSetColor(255,   0,   0); }  // angry
void headSetYellow()  { headSetColor(255, 255,   0); }  // humour
void headSetGreen()   { headSetColor(  0, 255,   0); }  // calm/relief
void headSetPink()    { headSetColor(255,   0, 128); }  // salsa/soft

// Short “colour wheel” animation for happy/expectant
void headColorWheelAnimation(unsigned long durationMs) {
  unsigned long start = millis();
  uint16_t offset = 0;
  while (millis() - start < durationMs) {
    for (uint8_t i = 0; i < HEAD_LED_COUNT; i++) {
      headStrip.setPixelColor(i, Wheel((i * 256 / HEAD_LED_COUNT + offset) & 255));
    }
    headStrip.show();
    offset++;
    delay(20);
  }
}

// Red–yellow alternating stripes (guilty)
void headRedYellowAltAnimation(unsigned long durationMs) {
  unsigned long start = millis();
  bool flip = false;
  while (millis() - start < durationMs) {
    for (uint8_t i = 0; i < HEAD_LED_COUNT; i++) {
      bool isRed = ((i + (flip ? 1 : 0)) % 2 == 0);
      if (isRed) {
        headStrip.setPixelColor(i, headColorRGB(255, 0, 0));     // red
      } else {
        headStrip.setPixelColor(i, headColorRGB(255, 255, 0));   // yellow
      }
    }
    headStrip.show();
    flip = !flip;
    delay(150);
  }
}

// ----- CIGAR NEOPIXEL (smoking ember) -----

void cigarSetColor(uint8_t r, uint8_t g, uint8_t b) {
  cigarStrip.setPixelColor(0, cigarColorRGB(r, g, b));
  cigarStrip.show();
}

void cigarOff() {
  cigarSetColor(0, 0, 0);
}

// Simple smoking animation: red/orange flicker
void cigarSmokeAnimation(unsigned long durationMs) {
  unsigned long start = millis();
  cigar.write(CIGAR_UP_ANGLE);  // lift cigar to mouth
  while (millis() - start < durationMs) {
    uint8_t red   = random(180, 255);
    uint8_t green = random(40, 120);  // orange-ish
    cigarSetColor(red, green, 0);
    delay(80);
  }
  // leave a dim ember until explicitly lowered
  cigarSetColor(120, 30, 0);
}

// ----- Gavel helpers -----

void gavelToRest() {
  gavel.write(GAVEL_REST_ANGLE);
}

void gavelBangOnce() {
  gavel.write(GAVEL_BANG_ANGLE);
  delay(150);
  gavelToRest();
  delay(100);
}

void gavelBangTwice() {
  gavelBangOnce();
  delay(120);
  gavelBangOnce();
}

// ----- Head movement helpers -----

void headLookCenter() { head.write(HEAD_CENTER_ANGLE); }
void headLookWife()   { head.write(HEAD_TOWARD_WIFE_ANGLE); }
void headLookChild()  { head.write(HEAD_TOWARD_CHILD_ANGLE); }
void headLookAway()   { head.write(HEAD_AWAY_ANGLE); }

// Dance entrance: head swings L–R
void headSwingDance() {
  for (int i = 0; i < 3; i++) {
    headLookChild();
    delay(180);
    headLookCenter();
    delay(120);
    headLookWife();
    delay(180);
    headLookCenter();
    delay(120);
  }
}

// Slow L–R scan
void headSlowLookLeftRight() {
  headLookChild();
  delay(250);
  headLookWife();
  delay(250);
  headLookCenter();
}

// “No, no” head shake
void headShakeNo() {
  for (int i = 0; i < 3; i++) {
    headLookChild();
    delay(120);
    headLookWife();
    delay(120);
  }
  headLookCenter();
}

// Slow jitter while looking toward wife
void headSlowJitterToWife() {
  headLookWife();
  for (int i = 0; i < 3; i++) {
    head.write(HEAD_TOWARD_WIFE_ANGLE - 5);
    delay(150);
    head.write(HEAD_TOWARD_WIFE_ANGLE + 5);
    delay(150);
  }
  headLookWife();
}

// Hands swinging alternately (gavel vs. cigar)
void handsSwingAltDance() {
  for (int i = 0; i < 3; i++) {
    // gavel up, cigar down
    gavel.write(GAVEL_BANG_ANGLE);
    cigar.write(CIGAR_DOWN_ANGLE);
    delay(180);
    // gavel down, cigar up
    gavelToRest();
    cigar.write(CIGAR_UP_ANGLE);
    delay(180);
  }
  cigar.write(CIGAR_DOWN_ANGLE);
  gavelToRest();
}

// Gavel + cigar jitter (case 15)
void gavelAndCigarJitter() {
  for (int i = 0; i < 6; i++) {
    gavel.write(GAVEL_BANG_ANGLE);
    cigar.write(CIGAR_UP_ANGLE);
    cigarSetColor(255, 50, 0);
    delay(80);
    gavelToRest();
    cigar.write(CIGAR_DOWN_ANGLE);
    cigarOff();
    delay(80);
  }
  cigar.write(CIGAR_DOWN_ANGLE);
  gavelToRest();
}

// ----- Setup helpers -----

void setupMusicMakerShield() {
  if (!musicPlayer.begin()) {
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1)
      ;
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD card failed or not present"));
    while (1)
      ;
  }

  musicPlayer.setVolume(20, 20);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
}

void setupServoMotors() {
  gavel.attach(GAVEL_SERVO_PIN);
  cigar.attach(CIGAR_SERVO_PIN);
  head.attach(HEAD_SERVO_PIN);

  gavelToRest();
  cigar.write(CIGAR_DOWN_ANGLE);
  headLookCenter();
}

void flashHeadPixels() {
  headSetDefault();
  cigarOff();
  delay(300);
  headSetColor(0, 0, 0);
  cigarOff();
  delay(150);
}

void setupRF24() {
  setupRF24Common();

  // Set us as a receiver
  radio.openWritingPipe(rcvrAddress);
  radio.openReadingPipe(1, xmtrAddress);

  Serial.println(F("I am a receiver"));
}

// MEERA / USER RECEIVER SETUP
void setup() {
  Serial.begin(9600);

  setupMusicMakerShield();
  setupServoMotors();

  headStrip.begin();
  headStrip.show();   // all off
  cigarStrip.begin();
  cigarStrip.show();  // all off

  setupRF24();
  flashHeadPixels();
}

// ----- Main loop: handle incoming cases -----

void loop() {
  radio.startListening();
  if (radio.available(&pipeNum)) {
    radio.read(&data, sizeof(data));

    Serial.print(F("message received Data = "));
    Serial.println(data.stateNumber);

    switch (data.stateNumber) {

      // ===== CASE 0–20: YOUR ROBOT MAPPING =====

      case 0:
        // DANCE ENTRANCE
        // Head colour wheel, head swings, hands swing alternately
        Serial.println(F("Case 0: Dance entrance"));
        headColorWheelAnimation(1500);  // short happy swirl
        headSwingDance();
        handsSwingAltDance();
        break;

      case 1:
        // Cigar, head turns to wife, Track101 “They look”, head yellow
        Serial.println(F("Case 1: Cigar + 'They look'"));
        cigarSmokeAnimation(800);       // quick puff, leave ember on
        headLookWife();
        musicPlayer.playFullFile("/track101.wav");
        headSetYellow();                // humour
        break;

      case 2:
        // Head to wife RED, Track401 “Court assumes Control”, Track402 “Blender”
        Serial.println(F("Case 2: Court assumes control + Blender"));
        headLookWife();
        headSetRed();                   // angry
        musicPlayer.playFullFile("/track401.wav");
        musicPlayer.playFullFile("/track402.wav");
        break;

      case 3:
        // Track403 “Logs”, head turns green
        Serial.println(F("Case 3: Logs"));
        musicPlayer.playFullFile("/track403.wav");
        headSetGreen();
        break;

      case 4:
        // Track404 “preposterous”, head red
        Serial.println(F("Case 4: Preposterous"));
        headSetRed();
        musicPlayer.playFullFile("/track404.wav");
        break;

      case 5:
        // Track405 “over a rug?”, head yellow
        Serial.println(F("Case 5: Over a rug?"));
        headSetYellow();
        musicPlayer.playFullFile("/track405.wav");
        break;

      case 6:
        // Track406 “impossible”, head yellow, head turns L to R
        Serial.println(F("Case 6: Impossible"));
        headSetYellow();
        musicPlayer.playFullFile("/track406.wav");
        headSlowLookLeftRight();
        break;

      case 7:
        // Track407 “Succulents”, head default (white)
        Serial.println(F("Case 7: Succulents"));
        musicPlayer.playFullFile("/track407.wav");
        headSetDefault();
        break;

      case 8:
        // Track408 “without wifi”, lower cigar, turn head to wife, head default
        Serial.println(F("Case 8: Without wifi"));
        cigar.write(CIGAR_DOWN_ANGLE);
        cigarOff();
        headLookWife();
        headSetDefault();
        musicPlayer.playFullFile("/track408.wav");
        break;

      case 9:
        // Track409 “objection”, gavel bang, head red
        Serial.println(F("Case 9: Objection"));
        headSetRed();
        gavelBangOnce();
        musicPlayer.playFullFile("/track409.wav");
        break;

      case 10:
        // Cigar, Track410 “No, I’m judicially”, head yellow
        Serial.println(F("Case 10: No, I'm judicially"));
        cigarSmokeAnimation(800);
        musicPlayer.playFullFile("/track410.wav");
        headSetYellow();
        break;

      case 11:
        // Track411 “Court adjourned”, gavel bang x2, head green
        Serial.println(F("Case 11: Court adjourned"));
        musicPlayer.playFullFile("/track411.wav");
        gavelBangTwice();
        headSetGreen();
        break;

      case 12:
        // Track501 “Court is now in session”, gavel bang, head default
        Serial.println(F("Case 12: Court is now in session"));
        gavelBangOnce();
        musicPlayer.playFullFile("/track501.wav");
        headSetDefault();
        break;

      case 13:
        // Track502 “Salsa encourages”, head pink
        Serial.println(F("Case 13: Salsa encourages"));
        musicPlayer.playFullFile("/track502.wav");
        headSetPink();
        break;

      case 14:
        // Turns to child, Track503 “Child,”, head colour wheel
        Serial.println(F("Case 14: Address child"));
        headLookChild();
        musicPlayer.playFullFile("/track503.wav");
        headColorWheelAnimation(1500);
        break;

      case 15:
        // Child says “I meant mother”
        // Gavel and cigar jitter, head red/yellow alt = guilty
        Serial.println(F("Case 15: Guilty jitter"));
        headRedYellowAltAnimation(1500);
        gavelAndCigarJitter();
        headSetRed();   // land on red (angry/guilty)
        break;

      case 16:
        // Track504 “child, that is priv”, head L to R (NO, NO), turns pink
        Serial.println(F("Case 16: Child, that is private"));
        musicPlayer.playFullFile("/track504.wav");
        headShakeNo();
        headSetPink();
        break;

      case 17:
        // Head turn (slow jitter) to wife, Track505 “say smtg”, head red/yellow alt
        Serial.println(F("Case 17: Say something"));
        headSlowJitterToWife();
        musicPlayer.playFullFile("/track505.wav");
        headRedYellowAltAnimation(1500);
        break;

      case 18:
        // Track506 “we were studying”, head turns away (L) and pink
        Serial.println(F("Case 18: We were studying"));
        musicPlayer.playFullFile("/track506.wav");
        headLookAway();
        headSetPink();
        break;

      case 19:
        // Track507 “court will be rec”, gavel bang x2
        Serial.println(F("Case 19: Court will be reconvened"));
        musicPlayer.playFullFile("/track507.wav");
        gavelBangTwice();
        break;

      case 20:
        // Track508 “too late”, cigar
        Serial.println(F("Case 20: Too late"));
        musicPlayer.playFullFile("/track508.wav");
        cigarSmokeAnimation(800);
        break;

      default:
        // Any unused state: reset to a neutral look
        Serial.println(F("Unknown state, resetting visuals"));
        headSetDefault();
        cigarOff();
        gavelToRest();
        headLookCenter();
        break;
    }
  }
}

// end of receiver code
// CHANGEHERE
*/