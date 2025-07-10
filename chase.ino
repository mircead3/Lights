#include <Adafruit_NeoPixel.h>
#define PIN 9 // Digital pin connected to the data input of the strip
#define NUMPIXELS 380 // Number of LEDs in the strip
#define NUMCOLORS 8   // number of predefined colors

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int brightness = 32;
int n = 2;    // number of pixels traveling together
int dist = 10; // distance between chasing pixels
int del = 50; // delay

void setup() {
  pixels.begin(); // Initialize NeoPixel library
}

int k = 0;

uint8_t colors[NUMCOLORS][3] = { // predefined colors; first one is black
  {0,0,0},
  {255,0,0},
  {0,255,0},
  {0,0,255},
  {255,255,0},
  {0,255,255},
  {255,0,255},
  {255,255,255}
};
uint8_t indices[NUMPIXELS];

void loop() {
  for (int i = NUMPIXELS-1; i > 0; i--) { // move one pixel forward
    int c = indices[i] = indices[i-1];
    pixels.setPixelColor(i, pixels.Color(colors[c][0], colors[c][1], colors[c][2]));
  }

  if (k < n) {
    // Introduce a new color for the first pixel
    indices[0] = random(1,NUMCOLORS-1);
  } else {
    indices[0] = 0; // black
  }
  pixels.setPixelColor(0, pixels.Color(colors[0][0], colors[0][1], colors[0][2]));
  pixels.setBrightness(brightness);
  pixels.show();
  delay(del);
  k = (k+1) % dist;
}
