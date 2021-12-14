#include <Arduino.h>
#include <WTV020SD16P.h>

static const uint8_t resetPin = 2; // The pin number of the reset pin.
static const uint8_t clockPin = 3; // The pin number of the clock pin.
static const uint8_t dataPin = 4; // The pin number of the data pin.
static const uint8_t busyPin = 5; // The pin number of the busy pin.

WTV020SD16P wtv020sd16p(resetPin, clockPin, dataPin, busyPin);

boolean stateOn = false;
unsigned long lastDebouncetime = 0;
unsigned long debounceDelay = 50;

boolean isPlaying = false;
boolean isPaused = false;
boolean stopTimer = false;
int16_t threshold = 100;
unsigned long pauseTime = 0;
unsigned long waitTime = 1000;


void setup() {
  Serial.begin(9600);
  wtv020sd16p.reset();
  // wtv020sd16p.setVolume(500);
}

void loop() {
  boolean currentStateOn = (analogRead(A7) < threshold) ? true : false;

  if (currentStateOn != stateOn) {
    lastDebouncetime = millis();
  }

  if((millis() - lastDebouncetime) > debounceDelay) {
    if (currentStateOn && isPlaying == false) {
      if (isPaused == false) {
        wtv020sd16p.playVoice(0);
        Serial.println("playing");
        Serial.println(digitalRead(5));
        isPlaying = true;
      }
      else {
        wtv020sd16p.pauseVoice();
        Serial.println("unpausing");
        Serial.println(digitalRead(5));
        isPlaying = true;
        isPaused = false;
        stopTimer = false;
      }
    }

    if (!currentStateOn && isPlaying == true) {
      wtv020sd16p.pauseVoice();
      Serial.println("pausing");
      Serial.println(digitalRead(5));
      isPlaying = false;
      isPaused = true;
      pauseTime = millis();
      stopTimer = true;
    }

    if (stopTimer == true && millis() - pauseTime >= waitTime) {
      wtv020sd16p.stopVoice();
      Serial.println("stopping");
      Serial.println(digitalRead(5));
      isPaused = false;
      stopTimer = false;
    }
  }

  stateOn = currentStateOn;
}