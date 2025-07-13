#include <Adafruit_NeoPixel.h>
#define PIN 9 // Digital pin connected to the data input of the strip
#define NUMPIXELS 376 // number of LEDs in the strip
#define NUMCOLORS 7   // number of predefined colors
#define MAXGROUPS 47  // maximum number of groups of LEDs travelling together
#define FADESIZE 7    // of the group tail (constant after that)
#define R 0           // indices in the colors array
#define G 1
#define B 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int numGroups = 1;
int groupSize = NUMPIXELS/numGroups;  // size of a group of pixels traveling together
int headSize = 1;                     // how many pixels are lit
int blackSize = groupSize-headSize;

int brightness = 255;
int del = 0; // delay

int colors[NUMCOLORS][3] = { // predefined colors
  {255,0,0},    // red
  {0,255,0},    // green
  {0,0,255},    // blue
  {255,255,0},  // yelow
  {0,255,255},  // cyan
  {255,0,255},  // magenta
  {255,255,255} // white
};

int fade[FADESIZE] {1,2,4,8,16,32,64};  // fadding factors
int defaultFade = 128;

int period = NUMCOLORS*groupSize;
int step = 0;  // repeats after period

void setup() {
  pixels.begin(); // Initialize NeoPixel library
  pixels.setBrightness(brightness);
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    int j = i + period - step;
    int index = j % groupSize; // in the group
    if (index < blackSize) { // in the black region
      pixels.setPixelColor(i, 0);
    } else {  // in the lit part
      int c = (j / groupSize) % NUMCOLORS; // group color
      int fi = groupSize - 1 - index;
      int f = fi < FADESIZE ? fade[fi] : defaultFade;
      pixels.setPixelColor(i, pixels.Color(colors[c][R]/f, colors[c][G]/f, colors[c][B]/f));
    }
  }

  pixels.show();
  delay(del);

  step++;
  if (step == period) {
    step = 0;
    headSize++;
    if (headSize > groupSize) {
      numGroups++;
      if (numGroups > MAXGROUPS) numGroups = 1;
      groupSize = NUMPIXELS/numGroups;
      period = NUMCOLORS*groupSize;
      headSize = 1;
    }
    blackSize = groupSize - headSize;
  }
}
