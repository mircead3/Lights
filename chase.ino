#include <Adafruit_NeoPixel.h>
#define PIN 9 // Digital pin connected to the data input of the strip
#define NUMPIXELS 70 // Number of LEDs in the strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int brightness = 32;
int n = 2;    // number of pixels traveling together
int dist = 8; // distance between chasing pixels
int del = 100; // delay

void setup() {
  pixels.begin(); // Initialize NeoPixel library
}

int k = 0;

int colors[NUMPIXELS][3];

void loop() {
  for (int i = NUMPIXELS-1; i > 0; i--) { // move one pixel forward
    for (int c = 0; c < 3; c++) colors[i][c] = colors[i-1][c];
    pixels.setPixelColor(i, pixels.Color(colors[i][0], colors[i][1], colors[i][2]));
  }

  if (k < n) {
    // Introduce a new color for the first pixel
    colors[0][0] = random(0,200);
    colors[0][1] = random(0,190);
    colors[0][2] = random(0,180);
  } else {
    colors[0][0] = colors[0][1] = colors[0][2] = 0;
  }
  pixels.setPixelColor(0, pixels.Color(colors[0][0], colors[0][1], colors[0][2]));
  pixels.setBrightness(brightness);
  pixels.show();
  delay(del);
  k = (k+1) % dist;
}
