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
// const int NRF_CE_PIN = A4, NRF_CSN_PIN = A5;

// CHANGEHERE
// for the receiver
const int NRF_CE_PIN = A11, NRF_CSN_PIN = A15;

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
/*
// Transmitter code

// Transmitter pin usage
const int LCD_RS_PIN = 3, LCD_EN_PIN = 2, LCD_D4_PIN = 4, LCD_D5_PIN = 5, LCD_D6_PIN = 6, LCD_D7_PIN = 7;
const int SW1_PIN = 8, SW2_PIN = 9, SW3_PIN = 10, SW4_PIN = A3, SW5_PIN = A2;

// LCD library code
#include <LiquidCrystal.h>

// initialize the library with the relevant pins
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

// EDIT
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
*/
// End of transmitter code
// CHANGEHERE

// Receiver Code
// CHANGEHERE

// Additional libraries for music maker shield
#include <Adafruit_VS1053.h>
#include <SD.h>

// Servo library
#include <Servo.h>

// NeoPixel strip for HEAD NEOPIXELS + CIGAR NEOPIXEL
#include <Adafruit_NeoPixel.h>

// ===== Music Maker Shield pins =====
#define SHIELD_RESET -1 // VS1053 reset pin (unused!)
#define SHIELD_CS 7     // VS1053 chip select pin (output)
#define SHIELD_DCS 6    // VS1053 Data/command select pin (output)
#define CARDCS 4        // SD card chip select pin
#define DREQ 3          // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(
    SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

// Connectors for NeoPixels and Servo Motors are labeled
// M1 - M6 with these pin assignments on nRF_Servo_Mega:
// M1 = 19
// M2 = 21
// M3 = 20
// M4 = 16
// M5 = 18
// M6 = 17
//
// Your mapping:
// M6 head servo
// M5 gavel servo
// M3 cigar servo
// M2 cigar NeoPixel  (16-pixel ring)
// M1 head NeoPixel   (16-pixel ring)
// M4 head NeoPixel   (16-pixel ring)

// ===== Servo pins =====
const int GAVEL_SERVO_PIN = 18; // M5: gavel
const int CIGAR_SERVO_PIN = 20; // M3: cigar
const int HEAD_SERVO_PIN = 17;  // M6: head

Servo gavel;
Servo cigar;
Servo head;

// Gavel angles
const int GAVEL_REST_ANGLE = 90; // neutral
const int GAVEL_UP_ANGLE = 90;   // up (semantic, same numeric for now)
const int GAVEL_BANG_ANGLE = 60; // down on table

// Cigar angles
const int CIGAR_DOWN_ANGLE = 30; // lowered, not smoking
const int CIGAR_UP_ANGLE = 120;  // up near mouth

// Head angles (tune in rehearsal)
const int HEAD_CENTER_ANGLE = 130; // facing front
const int HEAD_RIGHT_ANGLE = 90;   // turn right
const int HEAD_LEFT_ANGLE = 180;   // turn left

// ===== NeoPixel configuration =====
const uint8_t HEAD_LED_COUNT = 16;  // each head ring is 16 pixels
const uint8_t CIGAR_LED_COUNT = 16; // cigar ring is 16 pixels

const int HEAD_NEOPIXEL_PIN_1 = 19; // M1
const int HEAD_NEOPIXEL_PIN_2 = 16; // M4
const int CIGAR_NEOPIXEL_PIN = 21;  // M2

Adafruit_NeoPixel headStrip1 = Adafruit_NeoPixel(
    HEAD_LED_COUNT, HEAD_NEOPIXEL_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel headStrip2 = Adafruit_NeoPixel(
    HEAD_LED_COUNT, HEAD_NEOPIXEL_PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cigarStrip = Adafruit_NeoPixel(
    CIGAR_LED_COUNT, CIGAR_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// ----- Small helpers for colors and simple actions -----

// Map logical RGB to library's Color(r,g,b). The NEO_GRB flag
// inside Adafruit_NeoPixel handles the physical GRB wiring.
uint32_t headColorRGB(uint8_t r, uint8_t g, uint8_t b)
{
  return headStrip1.Color(r, g, b);
}

// For cigar: compensate wiring/type so that calling with
// (R,G,B) gives correct physical colour. Swap R and G
// before passing to Color().
uint32_t cigarColorRGB(uint8_t r, uint8_t g, uint8_t b)
{
  // arguments are desired RGB; we send GRB to match behaviour
  return cigarStrip.Color(r, g, b);
}

// Standard rainbow wheel for head ring (kept for reference, not used by cases now).
uint32_t Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    return headColorRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170)
  {
    WheelPos -= 85;
    return headColorRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return headColorRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// ----- HEAD NEOPIXELS (mood) -----

void headSetColor(uint8_t r, uint8_t g, uint8_t b)
{
  uint32_t c = headColorRGB(r, g, b);
  for (uint8_t i = 0; i < HEAD_LED_COUNT; i++)
  {
    headStrip1.setPixelColor(i, c);
    headStrip2.setPixelColor(i, c);
  }
  headStrip1.show();
  headStrip2.show();
}

// semantic wrappers (standard RGB)
void headSetDefault() { headSetColor(255, 255, 255); } // white = default
void headSetRed() { headSetColor(255, 0, 0); }         // angry
void headSetYellow() { headSetColor(255, 255, 0); }    // humour
void headSetGreen() { headSetColor(0, 255, 0); }       // calm/relief
void headSetPink() { headSetColor(255, 0, 128); }      // salsa/soft pink

// Case 0 / Case 14 colour wheel:
// PINK -> YELLOW -> PURPLE -> GREEN -> CYAN
// flashing one after the other in a loop.
void headColorWheelAnimation(unsigned long durationMs)
{
  const uint8_t COLORS[5][3] = {
      {255, 0, 128}, // pink   (R,G,B)
      {255, 255, 0}, // yellow
      {160, 0, 255}, // purple
      {0, 255, 0},   // green
      {0, 255, 255}  // cyan
  };

  unsigned long start = millis();
  uint8_t idx = 0;
  while (millis() - start < durationMs)
  {
    headSetColor(COLORS[idx][0], COLORS[idx][1], COLORS[idx][2]);
    delay(180);
    idx = (idx + 1) % 5;
  }
}

// Red–yellow alternating stripes (guilty)
void headRedYellowAltAnimation(unsigned long durationMs)
{
  unsigned long start = millis();
  bool flip = false;
  while (millis() - start < durationMs)
  {
    for (uint8_t i = 0; i < HEAD_LED_COUNT; i++)
    {
      bool isRed = ((i + (flip ? 1 : 0)) % 2 == 0);
      if (isRed)
      {
        headStrip1.setPixelColor(i, headColorRGB(255, 0, 0)); // red
        headStrip2.setPixelColor(i, headColorRGB(255, 0, 0));
      }
      else
      {
        headStrip1.setPixelColor(i, headColorRGB(255, 255, 0)); // yellow
        headStrip2.setPixelColor(i, headColorRGB(255, 255, 0));
      }
    }
    headStrip1.show();
    headStrip2.show();
    flip = !flip;
    delay(150);
  }
}

// Blushing: different shades of pink pulsing
void headBlushAnimation(unsigned long durationMs)
{
  const uint8_t SHADES[3][3] = {
      {255, 40, 140}, // light pink
      {255, 80, 180}, // brighter pink
      {255, 0, 128}   // base pink
  };

  unsigned long start = millis();
  uint8_t idx = 0;
  while (millis() - start < durationMs)
  {
    headSetColor(SHADES[idx][0], SHADES[idx][1], SHADES[idx][2]);
    delay(160);
    idx = (idx + 1) % 3;
  }
  // Land on soft pink
  headSetPink();
}

// ----- CIGAR NEOPIXEL (smoking ember / ring) -----

void cigarSetColor(uint8_t r, uint8_t g, uint8_t b)
{
  uint32_t c = cigarColorRGB(r, g, b);
  for (uint8_t i = 0; i < CIGAR_LED_COUNT; i++)
  {
    cigarStrip.setPixelColor(i, c);
  }
  cigarStrip.show();
}

void cigarOff()
{
  // actually off
  cigarSetColor(0, 0, 0);
}

// Simple smoking animation: red/orange flicker on the whole ring
void cigarSmokeAnimation(unsigned long durationMs)
{
  unsigned long start = millis();
  cigar.write(CIGAR_UP_ANGLE); // lift cigar to mouth
  while (millis() - start < durationMs)
  {
    uint8_t red = random(180, 255);
    uint8_t green = random(40, 120); // orange-ish
    cigarSetColor(red, green, 0);
    delay(80);
  }
  // leave a dim ember until explicitly lowered
  cigarSetColor(120, 30, 0);
}

// ----- Gavel helpers -----

void gavelToRest()
{
  gavel.write(GAVEL_REST_ANGLE);
}

void gavelUp()
{
  gavel.write(GAVEL_UP_ANGLE);
}

void gavelBangOnce()
{
  gavel.write(GAVEL_BANG_ANGLE);
  delay(150);
  gavelToRest();
  delay(100);
}

void gavelBangTwice()
{
  gavelBangOnce();
  delay(120);
  gavelBangOnce();
}

// ----- Head movement helpers -----

void headLookCenter() { head.write(HEAD_CENTER_ANGLE); }
void headLookRight() { head.write(HEAD_RIGHT_ANGLE); }
void headLookLeft() { head.write(HEAD_LEFT_ANGLE); }

// Default pose helper: head white + centered, gavel down, cigar down, cigar Neo off
void setDefaultPose()
{
  headSetDefault();              // head NeoPixels white
  headLookCenter();              // head servo center
  gavel.write(GAVEL_REST_ANGLE); // gavel down
  cigar.write(CIGAR_DOWN_ANGLE); // cigar down
  cigarOff();                    // cigar NeoPixels off
}


void danceEntranceCase0(unsigned long durationMs)
{
  // Combined "dance entrance" for Case 0:
  // - Head sways VERY SLOWLY LEFT <-> RIGHT
  // - Gavel and cigar move in alternating up/down pattern
  // - Head colour wheel: PINK -> YELLOW -> PURPLE -> GREEN -> CYAN

  const uint8_t COLORS[5][3] = {
      {255, 0, 128}, // pink
      {255, 255, 0}, // yellow
      {160, 0, 255}, // purple
      {0, 255, 0},   // green
      {0, 255, 255}  // cyan
  };

  // MUCH slower timings for a human-like, relaxed dance
  const unsigned long COLOR_INTERVAL = 1300;  // ms between colour changes
  const unsigned long HEAD_STEP_INT = 260;    // ms between head steps (slow)
  const unsigned long HAND_TOGGLE_INT = 1800; // ms between gavel/cigar swaps

  const int HEAD_STEP = 1;                     // degrees per step (tiny)
  const int HEAD_MIN_ANGLE = HEAD_LEFT_ANGLE;  // left limit
  const int HEAD_MAX_ANGLE = HEAD_RIGHT_ANGLE; // right limit

  // Initial state
  unsigned long startTime = millis();
  unsigned long lastColorChange = startTime;
  unsigned long lastHeadStep = startTime;
  unsigned long lastHandToggle = startTime;

  uint8_t colorIndex = 0;

  int headAngle = HEAD_CENTER_ANGLE;
  int headDir = -1; // -1 = moving toward left, +1 = toward right

  bool handsState = false; // false: gavel up, cigar down; true: gavel down, cigar up

  // Initialize positions and colour
  head.write(headAngle);
  gavelUp();
  cigar.write(CIGAR_DOWN_ANGLE);
  cigarOff();
  headSetColor(COLORS[colorIndex][0], COLORS[colorIndex][1], COLORS[colorIndex][2]);

  while (millis() - startTime < durationMs)
  {
    unsigned long now = millis();

    // ----- Update head colour wheel -----
    if (now - lastColorChange >= COLOR_INTERVAL)
    {
      lastColorChange = now;
      colorIndex = (colorIndex + 1) % 5;
      headSetColor(COLORS[colorIndex][0], COLORS[colorIndex][1], COLORS[colorIndex][2]);
    }

    // ----- Update head sway (VERY SLOW LEFT <-> RIGHT) -----
    if (now - lastHeadStep >= HEAD_STEP_INT)
    {
      lastHeadStep = now;

      headAngle += headDir * HEAD_STEP;

      // Bounce at edges
      if (headAngle <= HEAD_MIN_ANGLE)
      {
        headAngle = HEAD_MIN_ANGLE;
        headDir = +1;
      }
      else if (headAngle >= HEAD_MAX_ANGLE)
      {
        headAngle = HEAD_MAX_ANGLE;
        headDir = -1;
      }

      head.write(headAngle);
    }

    // ----- Update hands: gavel & cigar alternate up/down (slow) -----
    if (now - lastHandToggle >= HAND_TOGGLE_INT)
    {
      lastHandToggle = now;
      handsState = !handsState;

      if (!handsState)
      {
        // State 0: gavel UP, cigar down
        gavelUp();
        cigar.write(CIGAR_DOWN_ANGLE);
      }
      else
      {
        // State 1: gavel DOWN (bang-ish), cigar up
        gavel.write(GAVEL_BANG_ANGLE);
        cigar.write(CIGAR_UP_ANGLE);
      }
    }

    // Tiny pause so we don't hammer the CPU
    delay(10);
  }

  // Gently settle to neutral after dance
  headLookCenter();
  gavelToRest();
  cigar.write(CIGAR_DOWN_ANGLE);
}

// “No, no” head shake (kept as small, deliberate movement)
void headShakeNo()
{
  for (int i = 0; i < 3; i++)
  {
    headLookRight();
    delay(220);
    headLookLeft();
    delay(220);
  }
  headLookCenter();
}

// Slow left → right → left look (no jitter)
void headSlowJitterToWife()
{
  headLookLeft();
  delay(600);
  headLookRight();
  delay(600);
  headLookLeft();
  delay(600);
}

// Gavel + cigar accent (smoothed, no jittery twitch)
void gavelAndCigarJitter()
{
  // 3 slow accented motions rather than fast jitter
  for (int i = 0; i < 3; i++)
  {
    gavel.write(GAVEL_BANG_ANGLE);
    cigar.write(CIGAR_UP_ANGLE);
    cigarSetColor(255, 50, 0);
    delay(220);
    gavelToRest();
    cigar.write(CIGAR_DOWN_ANGLE);
    cigarOff();
    delay(220);
  }
  cigar.write(CIGAR_DOWN_ANGLE);
  gavelToRest();
}

// ----- Setup helpers -----

void setupMusicMakerShield()
{
  if (!musicPlayer.begin())
  {
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1)
      ;
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS))
  {
    Serial.println(F("SD card failed or not present"));
    while (1)
      ;
  }

  musicPlayer.setVolume(20, 20);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT); // DREQ int
}

void setupServoMotors()
{
  gavel.write(GAVEL_REST_ANGLE);
  gavel.attach(GAVEL_SERVO_PIN);
  cigar.write(CIGAR_DOWN_ANGLE);
  cigar.attach(CIGAR_SERVO_PIN);
  head.write(HEAD_CENTER_ANGLE);
  head.attach(HEAD_SERVO_PIN);
}

void flashHeadPixels()
{
  headSetDefault();
  cigarOff();
  delay(300);
  headSetColor(0, 0, 0);
  cigarOff();
  delay(150);
}

void setupRF24()
{
  setupRF24Common();

  // Set us as a receiver
  radio.openWritingPipe(rcvrAddress);
  radio.openReadingPipe(1, xmtrAddress);

  Serial.println(F("I am a receiver"));
}

// USER RECEIVER SETUP
void setup()
{
  Serial.begin(9600);

  setupMusicMakerShield();
  setupServoMotors();

  headStrip1.begin();
  headStrip1.show(); // all off
  headStrip2.begin();
  headStrip2.show(); // all off
  cigarStrip.begin();
  cigarStrip.show(); // all off

  setupRF24();
  flashHeadPixels();
}

// ----- Main loop: handle incoming cases -----

void loop()
{
  radio.startListening();
  if (radio.available(&pipeNum))
  {
    radio.read(&data, sizeof(data));

    Serial.print(F("message received Data = "));
    Serial.println(data.stateNumber);

    switch (data.stateNumber)
    {

      // ===== CASE 0–20: YOUR ROBOT MAPPING =====

    case 0:
      Serial.println(F("Case 0: Dance entrance"));
      danceEntranceCase0(6000); // run combined routine for ~6 seconds
      break;

    case 1:
      // Cigar
      // Head turns RIGHT
      // Track101 “They look”
      // Head turns yellow
      // then reprise Case 0 feel
      Serial.println(F("Case 1: Cigar + 'They look'"));
      cigarSmokeAnimation(800);       // quick puff, leave ember on
      musicPlayer.playFullFile("/track101.mp3");
      headSetYellow();
      setDefaultPose();
      break;

    case 2:
      // Head RIGHT RED
      // Track401 “Court assumes Control”
      // Track402 “Blender”
      Serial.println(F("Case 2: Court assumes control + Blender"));
      headLookRight();
      headSetRed();
      musicPlayer.playFullFile("/track401.mp3");
      musicPlayer.playFullFile("/track402.mp3");
      headLookCenter();
      break;

    case 3:
      // Track403 “Logs”
      // Head turns green
      Serial.println(F("Case 3: Logs"));
      musicPlayer.playFullFile("/track403.mp3");
      headSetGreen();
      break;

    case 4:
      // Track404 “preposterous”
      // Head turns red
      Serial.println(F("Case 4: Preposterous"));
      headSetRed();
      musicPlayer.playFullFile("/track404.mp3");
      break;

    case 5:
      // Track405 “over a rug?”
      // Head turns yellow
      Serial.println(F("Case 5: Over a rug?"));
      headSetYellow();
      musicPlayer.playFullFile("/track405.mp3");
      break;

    case 6:
      // Track406 “impossible”
      // Head turns yellow
      // Head turns LEFT to RIGHT NODDING NO
      Serial.println(F("Case 6: Impossible + NO nod"));
      headSetYellow();
      musicPlayer.playFullFile("/track406.mp3");
      headShakeNo();
      break;

    case 7:
      // Track407 “Succulents”
      // Head STAYS DEFAULT (WHITE)
      Serial.println(F("Case 7: Succulents"));
      musicPlayer.playFullFile("/track407.mp3");
      headSetDefault();
      setDefaultPose();
      break;

    case 8:
      // Track408 “without wifi”
      // Lower cigar, turn head RIGHT
      // Head STAYS default (white)
      Serial.println(F("Case 8: Without wifi"));
      cigarSmokeAnimation(800);       // quick puff, leave ember on
      cigarOff();
      headSetDefault();
      musicPlayer.playFullFile("/track408.mp3");
      setDefaultPose();
      break;

    case 9:
      // Track409 “objection”
      // Gavel bang (sound in track)
      // Head turns red
      Serial.println(F("Case 9: Objection"));
      headSetRed();
      gavelBangOnce();
      musicPlayer.playFullFile("/track409.mp3");
      setDefaultPose();
      break;

    case 10:
      // Cigar
      // Track 410 “No, I’m judicially”
      // Head turns yellow
      Serial.println(F("Case 10: No, I'm judicially"));
      cigarSmokeAnimation(800);
      musicPlayer.playFullFile("/track410.mp3");
      setDefaultPose();
      headSetYellow();
      break;

    case 11:
      // Track411 “Court adjourned”
      // Gavel bang x2
      // Head turns green
      Serial.println(F("Case 11: Court adjourned"));
      gavelBangTwice();
      musicPlayer.playFullFile("/track411.mp3");
      headSetGreen();
      setDefaultPose();
      break;

    case 12:
      // Track501 “Court is now in session”
      // Gavel bang
      // Head COLOR DEFAULT
      Serial.println(F("Case 12: Court is now in session"));
      gavelBangOnce();
      musicPlayer.playFullFile("/track501.mp3");
      headSetDefault();
      setDefaultPose();
      break;

    case 13:
      // Track502 “Salsa encourages”
      // Head turns pink (FLASHING DIFFERENT SHADES TO SHOW BLUSHING)
      Serial.println(F("Case 13: Salsa encourages (blushing)"));
      musicPlayer.playFullFile("/track502.mp3");
      headBlushAnimation(2000);
      setDefaultPose();
      break;

    case 14:
      // Turns to RIGHT
      // Track503 “Child,”
      // Head colour wheel (LIKE CASE 0)
      Serial.println(F("Case 14: Address child with colour wheel"));
      headLookRight(); // turn RIGHT
      musicPlayer.playFullFile("/track503.mp3");
      headColorWheelAnimation(2000);
      break;

    case 15:
      // Child says “i meant mother”
      // Head red yellow alt
      Serial.println(F("Case 15: Guilty red/yellow alt"));
      headRedYellowAltAnimation(2000);
      headSetRed(); // land on red
      setDefaultPose();
      break;

    case 16:
      // Track504 “child, that is priv”
      // Head L to R (NO, NO) turns pink (BLUSHING, SAME AS CASE 13)
      Serial.println(F("Case 16: Child, that is priv (NO + blush)"));
      musicPlayer.playFullFile("/track504.mp3");
      headShakeNo();
      headBlushAnimation(2000);
      setDefaultPose();
      break;

    case 17:
      // Head turn SLOWLY LEFT-RIGHT-LEFT
      // Track505 “say smtg”
      // Head red yellow alt
      Serial.println(F("Case 17: Say something (slow left-right-left + guilty lights)"));
      headSlowJitterToWife();
      musicPlayer.playFullFile("/track505.mp3");
      headRedYellowAltAnimation(2000);
      setDefaultPose();
      break;

    case 18:
      // Track506 “we were studying”
      // Head turns away (L) and pink
      Serial.println(F("Case 18: We were studying"));
      musicPlayer.playFullFile("/track506.mp3");
      headLookLeft();
      headBlushAnimation(2000);
      break;

    case 19:
      // Track507 “court will be rec”
      // Gavel bang x2
      Serial.println(F("Case 19: Court will be rec"));
      musicPlayer.playFullFile("/track507.mp3");
      gavelBangTwice();
      setDefaultPose();
      break;

    case 20:
      // Track508 “too late”
      // Cigar SERVO (UP)
      // CIGAR NEO LIGHTS RED
      Serial.println(F("Case 20: Too late (cigar up, red ring)"));
      musicPlayer.playFullFile("/track508.mp3");
      cigarSetColor(255, 0, 0);  // full red ring (now actually red)
      setDefaultPose();
      break;

    default:
      // Any unused state: reset to a neutral look
      Serial.println(F("Unknown state, resetting visuals"));
      setDefaultPose();
      break;
    }
  }
}

// end of receiver code
// CHANGEHERE
