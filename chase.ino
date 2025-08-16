#include <Adafruit_NeoPixel.h>
#define PIN 9 // Digital pin connected to the data input of the strip
#define NUMPIXELS 376 // 376 number of LEDs in the strip
#define MAXCOLORS 7   // number of predefined colors
#define NUMFADES 8    // number of fading factors
#define R 0           // indices in the colors array
#define G 1
#define B 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int colors[MAXCOLORS][3] = { // predefined colors
  {255,0,0},    // red
  {0,255,0},    // green
  {0,0,255},    // blue
  {255,255,0},  // yelow
  {0,255,255},  // cyan
  {255,0,255},  // magenta
  {255,255,255} // white
};

int fade[NUMFADES] {1,2,4,8,16,32,64,128};  // fading factors

int maxGroups = 4;                    // maximum number of group
int numColors = 7;                    // <= MAXCOLORS
int numFades = 6;                     // < NUMFADES, of the group tail (constant after that)
int defaultFade = fade[numFades];

int brightness = 200;
int del = 0; // delay

// Initial values
int numGroups = 1;
int groupSize = NUMPIXELS/numGroups;  // size of a group of pixels traveling together
int headSize = 1;                     // how many pixels are lit
int blackSize = groupSize-headSize;

int step = 0;  // repeats after period
int period = groupSize*numColors;

void setup() {
  pixels.begin(); // Initialize NeoPixel library
  pixels.setBrightness(brightness);
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    int j = i + period - step;
    int index = j % groupSize; // in the group, from the end
    if (index < blackSize) {   // in the black region
      if (index == blackSize-1) pixels.setPixelColor(i, 0);
    } else {                   // in the lit part
      int fi = groupSize - 1 - index;
      if (fi <= numFades) {
        int f = fi < numFades ? fade[fi] : defaultFade;
        int c = (j / groupSize) % numColors; // group color
        pixels.setPixelColor(i, pixels.Color(colors[c][R]/f, colors[c][G]/f, colors[c][B]/f));
      }
    }
  }

  pixels.show();
  delay(del);

  step++;
  if (step % groupSize == 0) {
    if (step == period) step = 0;
    headSize++;
    if (headSize > groupSize) {
      numGroups++;
      if (numGroups > maxGroups) numGroups = 1;
      groupSize = NUMPIXELS/numGroups;
      headSize = 1;
      period = groupSize*numColors;
    }
    blackSize = groupSize-headSize;
  }
}
