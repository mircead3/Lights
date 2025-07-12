#include <Adafruit_NeoPixel.h>
#define PIN 3 // Digital pin connected to the data input of the strip
#define NUMPIXELS 376 // Number of LEDs in the strip
#define NUMCOLORS 7   // number of predefined colors
#define TAILSIZE 5    // of the group leader (black after that)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int brightness = 232;
int groupSize = 94;   // size of a group of pixels traveling together, >= TAILSIZE
int del = 0; // delay

int colors[NUMCOLORS][3] = { // predefined colors
  {255,0,0},  // red
  {0,255,0},  // green
  {0,0,255},  // blue
  {255,255,0},
  {0,255,255},
  {255,0,255},
  {255,255,255} // white
};

int fade[TAILSIZE] {1,2,4,8,16};  // fadding factors

int period = NUMCOLORS*groupSize;
int step = 0;  // repeats after period

void setup() {
  pixels.begin(); // Initialize NeoPixel library
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    int j = i + period - step;
    int index = j % groupSize; // in the group
    if (index < groupSize - TAILSIZE) { // in the black region
      pixels.setPixelColor(i, 0);
    } else {  // in the tail
      int c = (j / groupSize) % NUMCOLORS; // group color
      int f = fade[groupSize - 1 - index];
      pixels.setPixelColor(i, pixels.Color(colors[c][0]/f, colors[c][1]/f, colors[c][2]/f));
    }
  }

  pixels.setBrightness(brightness);
  pixels.show();
  delay(del);
  step = (step+1) % period;
}
