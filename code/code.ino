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

// nRF24L01 uses SPI which is fixed
// on pins 11, 12, and 13 on the Uno
// and on pins 50, 51, and 52 on the Mega

// It also requires two other signals
// (CE = Chip Enable, CSN = Chip Select Not)
// Which can be any pins:

// CHANGEHERE
// For the transmitter (COMMENTED OUT for receiver build)
// const int NRF_CE_PIN = A4, NRF_CSN_PIN = A5;

// CHANGEHERE
// for the receiver (ACTIVE)
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

void setupRF24Common()
{
    if (!radio.begin())
    {
        Serial.println(F("radio  initialization failed"));
        while (1)
        {
        }
    }
    else
    {
        Serial.println(F("radio successfully initialized"));
    }
    radio.setDataRate(RF24_250KBPS);
    radio.setChannel(CUSTOM_CHANNEL_NUMBER);
    radio.setPALevel(RF24_POWER_LEVEL);
}

inline void release() { yield(); } // cooperative "no-delay" helper

// -----------------------------------------------------------------------------
// Transmitter code  (LEFT UNCHANGED, FULLY COMMENTED OUT)
// -----------------------------------------------------------------------------
/*

// Transmitter pin usage
const int LCD_RS_PIN = 3, LCD_EN_PIN = 2, LCD_D4_PIN = 4, LCD_D5_PIN = 5, LCD_D6_PIN = 6, LCD_D7_PIN = 7;
const int SW1_PIN = 8, SW2_PIN = 9, SW3_PIN = 10, SW4_PIN = A3, SW5_PIN = A2;

#include <LiquidCrystal.h>
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

// EDIT
const int NUM_OF_STATES = 20;
char* theStates[] = {
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
  "Scene 5.8"
};

void updateLCD() {
  lcd.clear();
  lcd.print(theStates[data.stateNumber]);
  lcd.setCursor(0, 1);
  lcd.print("not transmitted yet");
}

void countDown() {
  data.stateNumber = (data.stateNumber > 0) ? (data.stateNumber - 1) : 0;
  updateLCD();
}

void countUp() {
  if (++data.stateNumber >= NUM_OF_STATES) {
    data.stateNumber = NUM_OF_STATES - 1;
  }
  updateLCD();
}
void spare1() {}
void spare2() {}

void rf24SendData() {
  radio.stopListening();
  int retval = radio.write(&data, sizeof(data));

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("transmitting");
  lcd.setCursor(14, 0);
  lcd.print(data.stateNumber);

  Serial.print(F(" ... "));
  if (retval) {
    Serial.println(F("success"));
    lcd.setCursor(0, 1);
    lcd.print("success");
  } else {
    totalTransmitFailures++;
    Serial.print(F("failure, total failures = "));
    Serial.println(totalTransmitFailures);

    lcd.setCursor(0, 1);
    lcd.print("error, total=");
    lcd.setCursor(13, 1);
    lcd.print(totalTransmitFailures);
  }
}

class Button {
  int pinNumber;
  bool previousState;
  void (*buttonFunction)();
public:
  Button(int pn, void* bf) {
    pinNumber = pn;
    buttonFunction = bf;
    previousState = 1;
  }
  void update() {
    bool currentState = digitalRead(pinNumber);
    if (currentState == LOW && previousState == HIGH) {
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

void setupRF24() {
  setupRF24Common();
  radio.openWritingPipe(xmtrAddress);
  radio.openReadingPipe(1, rcvrAddress);
  Serial.println(F("I am a transmitter"));
  data.stateNumber = 0;
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Radio setup");
  lcd.setCursor(0, 1);
  lcd.print("addr 0x");
  lcd.setCursor(7, 1);
  char s[5];
  sprintf(s, "%02x", CUSTOM_ADDRESS_BYTE);
  lcd.print(s);
  lcd.setCursor(10, 1);
  lcd.print("ch");
  lcd.setCursor(13, 1);
  lcd.print(CUSTOM_CHANNEL_NUMBER);

  Serial.println(F("Setting up radio"));
  setupRF24();

  lcd.setCursor(0, 0);
  lcd.print("Radio OK state=");
  lcd.print(theStates[data.stateNumber]);

  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(SW2_PIN, INPUT_PULLUP);
  pinMode(SW3_PIN, INPUT_PULLUP);
  pinMode(SW4_PIN, INPUT_PULLUP);
  pinMode(SW5_PIN, INPUT_PULLUP);
}

void loop() {
  for (int i = 0; i < NUMBUTTONS; i++) {
    theButtons[i].update();
  }
  delay(50);  // (transmitter side delay is fine, remains unchanged)
}

void clearData() { data.stateNumber = 0; }

*/

// -----------------------------------------------------------------------------
// Receiver Code (ACTIVE)
// -----------------------------------------------------------------------------

// Additional libraries for music maker shield
#include <Adafruit_VS1053.h>
#include <SD.h>

// Servo library
#include <Servo.h>

// NeoPixel strips for HEAD + CIGAR
#include <Adafruit_NeoPixel.h>

// ===== Music Maker Shield pins =====
#define SHIELD_RESET -1
#define SHIELD_CS 7
#define SHIELD_DCS 6
#define CARDCS 4
#define DREQ 3

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(
    SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

// ===== M1–M6 pin map on nRF_Servo_Mega =====
// M1 = 19  (we'll use for CIGAR NeoPixel strip)
// M2 = 20  (HEAD NeoPixel strip)
// M3 = 21  (CIGAR servo)
// M4 = 16  (free)
// M5 = 18  (GAVEL servo)
// M6 = 17  (HEAD servo)

// ===== Servo pins =====
const int GAVEL_SERVO_PIN = 18; // M5
const int CIGAR_SERVO_PIN = 21; // M3
const int HEAD_SERVO_PIN = 17;  // M6

Servo gavel;
Servo cigar;
Servo head;

// ===== Calibratable angles =====
int GAVEL_REST_ANGLE = 60; // adjust on site
int GAVEL_BANG_ANGLE = 120;

int CIGAR_DOWN_ANGLE = 110;
int CIGAR_UP_ANGLE = 40;

int HEAD_CENTER_ANGLE = 90;
int HEAD_TOWARD_WIFE_ANGLE = 135; // right
int HEAD_TOWARD_CHILD_ANGLE = 45; // left
int HEAD_AWAY_ANGLE = 30;         // look away left

// ===== NeoPixel config =====
const int HEAD_NEOPIXEL_PIN = 20;   // M2
const int CIGAR_NEOPIXEL_PIN = 19;  // M1
const uint8_t HEAD_LED_COUNT = 15;  // "a couple of them around 15"
const uint8_t CIGAR_LED_COUNT = 12; // cigar strip has 12 pixels

Adafruit_NeoPixel headStrip(HEAD_LED_COUNT, HEAD_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cigarStrip(CIGAR_LED_COUNT, CIGAR_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// ===== Tracks =====
#define TRACK_EXT ".mp3" // change to ".wav" if your files are WAV

// helper to start audio without blocking
void playTrack(const char *path)
{
    musicPlayer.startPlayingFile(path); // async, returns immediately
}

// Quick path builders (8.3 filenames recommended on SD)
void play101() { playTrack("/track101" TRACK_EXT); }
void play401() { playTrack("/track401" TRACK_EXT); }
void play402() { playTrack("/track402" TRACK_EXT); }
void play403() { playTrack("/track403" TRACK_EXT); }
void play404() { playTrack("/track404" TRACK_EXT); }
void play405() { playTrack("/track405" TRACK_EXT); }
void play406() { playTrack("/track406" TRACK_EXT); }
void play407() { playTrack("/track407" TRACK_EXT); }
void play408() { playTrack("/track408" TRACK_EXT); }
void play409() { playTrack("/track409" TRACK_EXT); }
void play410() { playTrack("/track410" TRACK_EXT); }
void play411() { playTrack("/track411" TRACK_EXT); }
void play501() { playTrack("/track501" TRACK_EXT); }
void play502() { playTrack("/track502" TRACK_EXT); }
void play503() { playTrack("/track503" TRACK_EXT); }
void play504() { playTrack("/track504" TRACK_EXT); }
void play505() { playTrack("/track505" TRACK_EXT); }
void play506() { playTrack("/track506" TRACK_EXT); }
void play507() { playTrack("/track507" TRACK_EXT); }
void play508() { playTrack("/track508" TRACK_EXT); }
// optional sfx
void playGavelSFX() { playTrack("/sfx_gavl" TRACK_EXT); } // provide this on SD if desired

// ===== Color helpers =====
uint32_t rgb(Adafruit_NeoPixel &strip, uint8_t r, uint8_t g, uint8_t b)
{
    return strip.Color(r, g, b); // API handles GRB internally
}
void headFill(uint8_t r, uint8_t g, uint8_t b)
{
    for (uint8_t i = 0; i < HEAD_LED_COUNT; i++)
        headStrip.setPixelColor(i, rgb(headStrip, r, g, b));
    headStrip.show();
}
void cigarFill(uint8_t r, uint8_t g, uint8_t b)
{
    for (uint8_t i = 0; i < CIGAR_LED_COUNT; i++)
        cigarStrip.setPixelColor(i, rgb(cigarStrip, r, g, b));
    cigarStrip.show();
}

// semantic head colors
void headDefault() { headFill(255, 255, 255); }
void headRed() { headFill(255, 0, 0); }
void headYellow() { headFill(255, 255, 0); }
void headGreen() { headFill(0, 255, 0); }
void headPink() { headFill(255, 0, 128); }
void headOff() { headFill(0, 0, 0); }
void cigarOff() { cigarFill(0, 0, 0); }

// ===== Non-blocking animation state =====
unsigned long nowMs;

// Head colour wheel
bool animHeadWheel = false;
unsigned long headWheelLast = 0;
uint16_t headWheelOffset = 0;
uint16_t headWheelInterval = 20; // ms

// Head L-R swing (dance)
bool animHeadSwingDance = false;
unsigned long headSwingLast = 0;
uint8_t headSwingPhase = 0;
uint16_t headSwingInterval = 160;

// Hands alt swing (gavel/cigar)
bool animHandsAlt = false;
unsigned long handsAltLast = 0;
bool handsAltFlip = false;
uint16_t handsAltInterval = 180;

// Cigar smoking flicker
bool animCigarSmoke = false;
unsigned long cigarLast = 0;
uint16_t cigarInterval = 80;

// Head red-yellow alternating bands
bool animHeadRedYellowAlt = false;
unsigned long headAltLast = 0;
bool headAltFlip = false;
uint16_t headAltInterval = 150;

// Head slow scan L-R
bool animHeadScan = false;
unsigned long headScanLast = 0;
uint8_t headScanPhase = 0;
uint16_t headScanInterval = 250;

// Head "NO NO" shake
bool animHeadShakeNo = false;
unsigned long headShakeLast = 0;
uint8_t headShakeCount = 0;
uint16_t headShakeInterval = 120;
uint8_t headShakeMaxPairs = 6; // 3 full "no" cycles

// Head slow jitter while facing wife
bool animHeadSlowJitterWife = false;
unsigned long headJitterLast = 0;
bool headJitterFlip = false;
uint16_t headJitterInterval = 150;

// Gavel bang sequence
bool animGavelBang = false;
unsigned long gavelLast = 0;
uint8_t gavelPhase = 0; // 0=go down, 1=rest
uint8_t gavelTimesLeft = 0;
uint16_t gavelDownHold = 120;
uint16_t gavelRestHold = 120;
bool gavelWithSFX = false;

// Gavel + cigar jitter (case 15)
bool animJitterBoth = false;
unsigned long jitterLast = 0;
uint8_t jitterCount = 0;
uint8_t jitterMax = 12;
uint16_t jitterInterval = 80;

// Program chaining (auto-return to another case)
bool programActive = false;
unsigned long programEndsAt = 0;
int queuedNextState = -1;

// Current state tracking
int currentState = -1;

// ===== Animation updaters (non-blocking) =====
void updateHeadWheel()
{
    if (!animHeadWheel)
        return;
    if (nowMs - headWheelLast < headWheelInterval)
        return;
    headWheelLast = nowMs;
    for (uint8_t i = 0; i < HEAD_LED_COUNT; i++)
    {
        uint8_t pos = (i * 256 / HEAD_LED_COUNT + headWheelOffset) & 255;
        uint32_t col;
        if (pos < 85)
            col = rgb(headStrip, pos * 3, 255 - pos * 3, 0);
        else if (pos < 170)
        {
            pos -= 85;
            col = rgb(headStrip, 255 - pos * 3, 0, pos * 3);
        }
        else
        {
            pos -= 170;
            col = rgb(headStrip, 0, pos * 3, 255 - pos * 3);
        }
        headStrip.setPixelColor(i, col);
    }
    headStrip.show();
    headWheelOffset++;
}

void updateHeadRedYellowAlt()
{
    if (!animHeadRedYellowAlt)
        return;
    if (nowMs - headAltLast < headAltInterval)
        return;
    headAltLast = nowMs;
    headAltFlip = !headAltFlip;
    for (uint8_t i = 0; i < HEAD_LED_COUNT; i++)
    {
        bool red = ((i + (headAltFlip ? 1 : 0)) % 2 == 0);
        headStrip.setPixelColor(i, red ? rgb(headStrip, 255, 0, 0) : rgb(headStrip, 255, 255, 0));
    }
    headStrip.show();
}

void updateHeadSwingDance()
{
    if (!animHeadSwingDance)
        return;
    if (nowMs - headSwingLast < headSwingInterval)
        return;
    headSwingLast = nowMs;
    switch (headSwingPhase)
    {
    case 0:
        head.write(HEAD_TOWARD_CHILD_ANGLE);
        break;
    case 1:
        head.write(HEAD_CENTER_ANGLE);
        break;
    case 2:
        head.write(HEAD_TOWARD_WIFE_ANGLE);
        break;
    case 3:
        head.write(HEAD_CENTER_ANGLE);
        break;
    }
    headSwingPhase = (headSwingPhase + 1) & 3;
}

void updateHandsAlt()
{
    if (!animHandsAlt)
        return;
    if (nowMs - handsAltLast < handsAltInterval)
        return;
    handsAltLast = nowMs;
    handsAltFlip = !handsAltFlip;
    if (handsAltFlip)
    {
        gavel.write(GAVEL_BANG_ANGLE);
        cigar.write(CIGAR_DOWN_ANGLE);
    }
    else
    {
        gavel.write(GAVEL_REST_ANGLE);
        cigar.write(CIGAR_UP_ANGLE);
    }
}

void updateCigarSmoke()
{
    if (!animCigarSmoke)
        return;
    if (nowMs - cigarLast < cigarInterval)
        return;
    cigarLast = nowMs;
    cigar.write(CIGAR_UP_ANGLE);
    uint8_t r = random(180, 255);
    uint8_t g = random(40, 120);
    cigarFill(r, g, 0);
}

void updateHeadScan()
{
    if (!animHeadScan)
        return;
    if (nowMs - headScanLast < headScanInterval)
        return;
    headScanLast = nowMs;
    switch (headScanPhase)
    {
    case 0:
        head.write(HEAD_TOWARD_CHILD_ANGLE);
        break;
    case 1:
        head.write(HEAD_TOWARD_WIFE_ANGLE);
        break;
    case 2:
        head.write(HEAD_CENTER_ANGLE);
        break;
    }
    headScanPhase = (headScanPhase + 1) % 3;
}

void updateHeadShakeNo()
{
    if (!animHeadShakeNo)
        return;
    if (nowMs - headShakeLast < headShakeInterval)
        return;
    headShakeLast = nowMs;
    if (headShakeCount >= headShakeMaxPairs)
    {
        animHeadShakeNo = false;
        head.write(HEAD_CENTER_ANGLE);
        return;
    }
    // toggle between left/right
    if (headShakeCount % 2 == 0)
        head.write(HEAD_TOWARD_CHILD_ANGLE);
    else
        head.write(HEAD_TOWARD_WIFE_ANGLE);
    headShakeCount++;
}

void updateHeadSlowJitterWife()
{
    if (!animHeadSlowJitterWife)
        return;
    if (nowMs - headJitterLast < headJitterInterval)
        return;
    headJitterLast = nowMs;
    headJitterFlip = !headJitterFlip;
    head.write(HEAD_TOWARD_WIFE_ANGLE + (headJitterFlip ? 5 : -5));
}

void updateGavelBang()
{
    if (!animGavelBang)
        return;
    if (gavelPhase == 0)
    {
        // move down and trigger SFX once per bang
        gavel.write(GAVEL_BANG_ANGLE);
        if (gavelWithSFX)
            playGavelSFX();
        gavelPhase = 1;
        gavelLast = nowMs;
    }
    else
    {
        if (nowMs - gavelLast >= gavelDownHold)
        {
            gavel.write(GAVEL_REST_ANGLE);
            gavelPhase = 2;
            gavelLast = nowMs;
        }
        if (gavelPhase == 2 && (nowMs - gavelLast >= gavelRestHold))
        {
            if (gavelTimesLeft > 1)
            {
                gavelTimesLeft--;
                gavelPhase = 0; // next bang
            }
            else
            {
                animGavelBang = false; // finished
            }
        }
    }
}

void updateJitterBoth()
{
    if (!animJitterBoth)
        return;
    if (nowMs - jitterLast < jitterInterval)
        return;
    jitterLast = nowMs;
    bool on = (jitterCount % 2 == 0);
    if (on)
    {
        gavel.write(GAVEL_BANG_ANGLE);
        cigar.write(CIGAR_UP_ANGLE);
        cigarFill(255, 60, 0);
    }
    else
    {
        gavel.write(GAVEL_REST_ANGLE);
        cigar.write(CIGAR_DOWN_ANGLE);
        cigarOff();
    }
    jitterCount++;
    if (jitterCount >= jitterMax)
    {
        animJitterBoth = false;
    }
}

// ===== Control helpers =====
void headCenter() { head.write(HEAD_CENTER_ANGLE); }
void headWife() { head.write(HEAD_TOWARD_WIFE_ANGLE); }
void headChild() { head.write(HEAD_TOWARD_CHILD_ANGLE); }
void headAway() { head.write(HEAD_AWAY_ANGLE); }

void stopAllAnimations()
{
    animHeadWheel = false;
    animHeadSwingDance = false;
    animHandsAlt = false;
    animCigarSmoke = false;
    animHeadRedYellowAlt = false;
    animHeadScan = false;
    animHeadShakeNo = false;
    animHeadSlowJitterWife = false;
    animGavelBang = false;
    animJitterBoth = false;
}

void startGavel(uint8_t times, bool withSfx)
{
    animGavelBang = true;
    gavelPhase = 0;
    gavelTimesLeft = times;
    gavelWithSFX = withSfx;
}

void startProgramTimer(uint16_t durationMs, int nextState)
{
    programActive = true;
    programEndsAt = nowMs + durationMs;
    queuedNextState = nextState;
}

void maybeChainProgram()
{
    if (!programActive)
        return;
    if ((long)(nowMs - programEndsAt) >= 0)
    {
        programActive = false;
        if (queuedNextState >= 0)
        {
            data.stateNumber = queuedNextState; // simulate a radio command
            queuedNextState = -1;
            // apply immediately
            Serial.print(F("Auto-chain to state "));
            Serial.println(data.stateNumber);
            // fall through to apply behavior:
            // (we call the same handler used by radio updates)
            // to avoid code dup:
            // handled at the end of loop after updates
        }
    }
}

// ===== Receiver setup =====
void setupMusicMakerShield()
{
    if (!musicPlayer.begin())
    {
        Serial.println(F("Couldn't find VS1053, check pins."));
        while (1)
        {
            release();
        }
    }
    if (!SD.begin(CARDCS))
    {
        Serial.println(F("SD card failed or not present"));
        while (1)
        {
            release();
        }
    }
    musicPlayer.setVolume(20, 20);
    musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT); // async
}

void setupServoMotors()
{
    gavel.attach(GAVEL_SERVO_PIN);
    cigar.attach(CIGAR_SERVO_PIN);
    head.attach(HEAD_SERVO_PIN);
    gavel.write(GAVEL_REST_ANGLE);
    cigar.write(CIGAR_DOWN_ANGLE);
    head.write(HEAD_CENTER_ANGLE);
}

void setupRF24()
{
    setupRF24Common();
    radio.openWritingPipe(rcvrAddress);
    radio.openReadingPipe(1, xmtrAddress);
    Serial.println(F("I am a receiver"));
}

void flashHeadPixels()
{
    headDefault();
    cigarOff();
    unsigned long t0 = millis();
    while (millis() - t0 < 300)
    {
        release();
    }
    headOff();
    cigarOff();
    t0 = millis();
    while (millis() - t0 < 150)
    {
        release();
    }
}

// ===== Apply behavior per state (non-blocking) =====
void applyCaseBehavior(uint8_t s)
{
    stopAllAnimations();
    headCenter();
    // (leave audio playing if a previous track is still going; starting a new one will override)

    switch (s)
    {
    case 0:
        // DANCE ENTRANCE: Head colour wheel, Head swings, Hands swings alt
        animHeadWheel = true;
        animHeadSwingDance = true;
        animHandsAlt = true;
        break;

    case 1:
        // Cigar, Head -> wife, Track101 “They look”, Head yellow, then return to Case 0
        animCigarSmoke = true;
        headWife();
        play101();
        headYellow();
        startProgramTimer(2000, 0); // auto-chain to case 0 after 2s
        break;

    case 2:
        // Head -> wife RED, 401 “Court assumes Control”, 402 “Blender”, 001 typing (we'll play 401 then 402)
        headWife();
        headRed();
        play401();
        // allow overlap; start 402 shortly after using timer
        startProgramTimer(800, -1); // after 0.8s kick 402
        break;

    case 3:
        // 403 “Logs”, Head green, 001 typing (green calm)
        headGreen();
        play403();
        break;

    case 4:
        // 404 “preposterous”, Head red
        headRed();
        play404();
        break;

    case 5:
        // 405 “over a rug?”, Head yellow
        headYellow();
        play405();
        break;

    case 6:
        // 406 “impossible”, Head yellow, Head turns L to R
        headYellow();
        animHeadScan = true;
        play406();
        break;

    case 7:
        // 407 “Succulents”, Head default (white)
        headDefault();
        play407();
        break;

    case 8:
        // 408 “without wifi”, Lower cigar, Head -> wife, Head default
        cigar.write(CIGAR_DOWN_ANGLE);
        cigarOff();
        headWife();
        headDefault();
        play408();
        break;

    case 9:
        // 409 “objection”, Gavel bang (with SFX), Head red
        headRed();
        startGavel(1, true);
        play409();
        break;

    case 10:
        // Cigar, 410 “No, I’m judicially”, Head yellow
        animCigarSmoke = true;
        headYellow();
        play410();
        break;

    case 11:
        // 411 “Court adjourned”, Gavel bang x2, Head green
        startGavel(2, true);
        headGreen();
        play411();
        break;

    case 12:
        // 501 “Court is now in session”, Gavel bang, Head default
        startGavel(1, true);
        headDefault();
        play501();
        break;

    case 13:
        // 502 “Salsa encourages”, Head pink
        headPink();
        play502();
        break;

    case 14:
        // Turns to child, 503 “Child,”, Head colour wheel
        headChild();
        play503();
        animHeadWheel = true;
        break;

    case 15:
        // Child says “i meant mother” -> Gavel and cigar jitter, Head red yellow alt
        animHeadRedYellowAlt = true;
        animJitterBoth = true;
        jitterCount = 0;
        playGavelSFX(); // optional accent at start
        break;

    case 16:
        // 504 “child, that is priv”, Head L to R (NO, NO), turns pink
        play504();
        headPink();
        animHeadShakeNo = true;
        headShakeCount = 0;
        break;

    case 17:
        // Head slow jitter to wife, 505 “say smtg”, Head red yellow alt
        headWife();
        animHeadSlowJitterWife = true;
        animHeadRedYellowAlt = true;
        play505();
        break;

    case 18:
        // 506 “we were studying”, Head turns away (L) and pink
        headAway();
        headPink();
        play506();
        break;

    case 19:
        // 507 “court will be rec”, Gavel bang x2
        startGavel(2, true);
        play507();
        break;

    case 20:
        // 508 “too late”, Cigar
        animCigarSmoke = true;
        play508();
        break;

    default:
        headDefault();
        cigarOff();
        gavel.write(GAVEL_REST_ANGLE);
        break;
    }

    currentState = s;
}

// ===== Arduino setup/loop =====
void setup()
{
    Serial.begin(9600);
    randomSeed(analogRead(A0));

    setupMusicMakerShield();
    setupServoMotors();

    headStrip.begin();
    headStrip.show();
    cigarStrip.begin();
    cigarStrip.show();

    setupRF24();
    flashHeadPixels();

    currentState = -1;
}

void loop()
{
    nowMs = millis();

    // chain timed programs and auxiliary track starts (case 2 402 kick)
    if (programActive)
    {
        // special helper: if we queued 402 after 401 in case 2
        if (currentState == 2 && (long)(nowMs - (programEndsAt - 800)) >= 0 && (long)(nowMs - (programEndsAt - 799)) < 2)
        {
            play402();
        }
        maybeChainProgram();
    }

    // radio handling
    radio.startListening();
    if (radio.available(&pipeNum))
    {
        radio.read(&data, sizeof(data));
        Serial.print(F("message received Data = "));
        Serial.println(data.stateNumber);
        applyCaseBehavior(data.stateNumber);
    }

    // run non-blocking animations
    updateHeadWheel();
    updateHeadRedYellowAlt();
    updateHeadSwingDance();
    updateHandsAlt();
    updateCigarSmoke();
    updateHeadScan();
    updateHeadShakeNo();
    updateHeadSlowJitterWife();
    updateGavelBang();
    updateJitterBoth();

    release(); // cooperative yield
}
