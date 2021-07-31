#include "FastLED.h"

#define NUM_LEDS 300
#define LED_PIN 7
#define SENSETIVITY A5
#define MICRO_SENSOR A0

#define PURPLE_RGB_THRESHOLD 90
#define BLUE_RGB_THRESHOLD 80
#define GREEN_RGB_THRESHOLD 70
#define WHITE_RGB_THRESHOLD 60

CRGB leds[NUM_LEDS];
int sensorValue = 0;
float sensitivityValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(MICRO_SENSOR, INPUT);
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(100);
  pinMode(7, OUTPUT);
  pinMode(SENSETIVITY, INPUT);
  for (int i = 0; i < NUM_LEDS; i++ ) {
    leds[i] = CRGB::Black;
  }
}
void loop() {
  sensorValue = analogRead(MICRO_SENSOR) - 510;
  sensorValue = abs(sensorValue);
  sensitivityValue = map(analogRead(SENSETIVITY), 0, 1024, 100, 0) / 100.0;
  for (int i = NUM_LEDS - 2; i >= 0; i-- ) {
    leds[i+1] = leds[i];
  }

  if (sensorValue / sensitivityValue > PURPLE_RGB_THRESHOLD) {
    leds[0] = CRGB(111, 255, 0);
  }
  else if(sensorValue / sensitivityValue > BLUE_RGB_THRESHOLD){
    leds[0] = CRGB::Green;
  }
  else if(sensorValue / sensitivityValue > GREEN_RGB_THRESHOLD){
    leds[0] = CRGB::Blue;
  }
  else if(sensorValue / sensitivityValue > WHITE_RGB_THRESHOLD){
    leds[0] = CRGB::White;
  }
  else
  {
     leds[0] = CRGB::Black;
  }

  FastLED.show();
  delay(10);
}
