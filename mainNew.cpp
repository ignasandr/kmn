#include <Arduino.h>
#include <WTV020SD16P.h>

static const uint8_t resetPin = 2; // The pin number of the reset pin.
static const uint8_t clockPin = 3; // The pin number of the clock pin.
static const uint8_t dataPin = 4; // The pin number of the data pin.
static const uint8_t busyPin = 5; // The pin number of the busy pin.

WTV020SD16P wtv020sd16p(resetPin, clockPin, dataPin, busyPin);

boolean isPlaying = false;
boolean stopTimer = false;
int16_t threshold = 100;
unsigned long pauseTime = 0;
unsigned long waitTime = 1000;


void setup() {
  Serial.begin(9600);
  wtv020sd16p.reset();
  // wtv020sd16p.setVolume(50);
}

void loop() {
  boolean stateOn = (analogRead(A7) < threshold) ? true : false;

    if (stateOn && isPlaying == false) {
      wtv020sd16p.asyncPlayVoice(0);
      Serial.println("playing");
      Serial.println(stateOn);
      isPlaying = true;
      stopTimer = false;
    }
    else if(!stateOn && isPlaying == true) {
      wtv020sd16p.stopVoice();
      Serial.println("stopping");
      isPlaying = false;
    }

    // if (stateOn && isPlaying == true && stopTimer == true) {
    //   stopTimer = false; 
    // }

    // if (!stateOn && isPlaying == true && stopTimer == false) {
    //   Serial.println("Starting countdown timer");
    //   pauseTime = millis();
    //   stopTimer = true;
    // }

    // if (stopTimer == true && millis() - pauseTime >= waitTime) {
    //   wtv020sd16p.stopVoice();
    //   Serial.println("stopping");
    //   stopTimer = false;
    //   isPlaying = false;
    // }
}