#include <Arduino.h>
#include <WTV020SD16P.h>

static const uint8_t resetPin = 2; // The pin number of the reset pin.
static const uint8_t clockPin = 3; // The pin number of the clock pin.
static const uint8_t dataPin = 4; // The pin number of the data pin.
static const uint8_t busyPin = 5; // The pin number of the busy pin.

WTV020SD16P wtv020sd16p(resetPin, clockPin, dataPin, busyPin);

boolean isPlaying = false;
boolean isPaused = false;
boolean stopTimer = false;
int16_t threshold = 100;
unsigned long pauseTime = 0;
unsigned long waitTime = 5000;


void play();

void setup() {
  Serial.begin(9600);
  // wtv020sd16p.reset();
}

void loop() {

  // Serial.println(analogRead(A7));
  // delay(1000);

  if (analogRead(A7) < threshold && isPlaying == false) {
    if (isPaused == false) {
      Serial.println("playing");
      isPlaying = true;
    }
    else {
      Serial.println("unpausing");
      isPlaying = true;
      isPaused = false;
      stopTimer = false;
    }
  }

  if (analogRead(A7) > threshold && isPlaying == true) {
    Serial.println("pausing");
    isPlaying = false;
    isPaused = true;
    pauseTime = millis();
    stopTimer = true;
  }

  if (stopTimer == true && millis() - pauseTime >= waitTime) {
    Serial.println("stopping");
    isPaused = false;
    stopTimer = false;
  }

  // if (analogRead(A7) < threshold && isPlaying == false && isPaused == false) {
  //   // wtv020sd16p.asyncPlayVoice(0);
  //   Serial.println("Starting playback");
  //   isPlaying = true;
  // }
  // else if (analogRead(A7) < threshold && isPlaying == true && isPaused == true) {
  //   // wtv020sd16p.pauseVoice();
  //   Serial.println("Unpausing playback");
  //   isPaused = false;
  // } // if paused, unpause
  // else if (analogRead(A7) > threshold && isPlaying == true && isPaused == false) {
  //   // wtv020sd16p.pauseVoice();
  //   Serial.println("Pausing playback");
  //   isPaused == true;
  // } // if light is on pause voice


  // switch(analogRead(A7) < threshold) {
  //       case true: 
  //           switch(isPlaying) {
  //             case false:
  //               switch(isPaused) {
  //                 case false:
  //                   Serial.println("starting playback");
  //                   isPlaying = true;
  //                   break;
  //                 case true:
  //                   break;
  //               }
  //               break;
  //             case true:
  //               switch(isPaused) {
  //                 case false:
  //                   break;
  //                 case true:
  //                   Serial.println("unpausing playback");
  //                   isPaused = false;
  //                   break;
  //               }
  //               break;
  //           }
  //           break;
  //       case false:
  //           switch(isPlaying) {
  //             case false:
  //               break;
  //             case true:
  //               switch(isPaused) {
  //                 case true:
  //                   break;
  //                 case false:
  //                   Serial.println("pausing playback");
  //                   isPaused = true;
  //                   break;
  //               }
  //               break;
  //           }
  //           break;
    // }

}



