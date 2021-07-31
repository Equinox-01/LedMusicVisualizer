#include "FastLED.h"

#define NUM_LEDS 300
#define MICRO_SENSETIVITY_THRESHOLD 510
#define LED_PIN 7
#define MUTE_LEVEL 60

#define SENSETIVITY A5
#define MICRO_SENSOR A0

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(MICRO_SENSOR, INPUT);
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(100);
  pinMode(SENSETIVITY, INPUT);
  for (int i = 0; i < NUM_LEDS; i++ ) {
    leds[i] = CRGB::Black;
  }
}
void loop() {
  int sensorValue = abs(analogRead(MICRO_SENSOR) - MICRO_SENSETIVITY_THRESHOLD);
  float sensitivityValue = map(analogRead(SENSETIVITY), 0, 1024, 100, 0) / 100.0;

  for (int i = NUM_LEDS - 2; i >= 0; i-- ) {
    leds[i+1] = leds[i];
  }

  int color_level = sensorValue / sensitivityValue;
  if (color_level > MUTE_LEVEL) {
    leds[0] = NumberToRGBColor(color_level);
  }
  else{
    leds[0] = CRGB::Black;
  }
  FastLED.show();
  delay(10);
}

CRGB NumberToRGBColor(int number){
  number = map(number, 0, 250, 0, 65535);
  int red = number >> 11;
  int green = (number >> 5) & 63;
  int blue = number & 31;

  red = red * 255 / 31;
  green = green * 255 / 63;
  blue = blue * 255 / 31;
  
  return CRGB(red, green, blue);
}
