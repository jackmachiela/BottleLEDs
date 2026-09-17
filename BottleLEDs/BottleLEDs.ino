// BottleLights
// Single 5V WS2812B addressable RGB LED strip (5m)
// - Pot 1 (A0): sets color, sweeping through the color wheel
// - Pot 2 (A1): sets overall brightness (dimmer)
// Requires the FastLED library (install via Library Manager in the Arduino IDE)

#include <FastLED.h>

const int DATA_PIN = 6;

// 30 LEDs/m, per the strip's actual spec, over a single 5m run.
const int LED_DENSITY_PER_M = 30;
const int STRIP_LENGTH_M = 5;
const int NUM_LEDS = LED_DENSITY_PER_M * STRIP_LENGTH_M;

CRGB leds[NUM_LEDS];

const int COLOR_POT_PIN = A0;
const int BRIGHTNESS_POT_PIN = A1;

// Smooths out noisy pot readings so the color doesn't jitter
const int SMOOTHING_SAMPLES = 8;

// Brightness ceilings (0-255), regardless of the brightness pot's position.
// These cap the total current the strip can ever draw, so pick them
// based on what your 5V supply is actually rated for. Two separate caps
// because white draws more current per LED than any wheel color can:
//
// - MAX_BRIGHTNESS_COLOR: applies at full saturation (this code uses
//   S=255 for wheel colors, so at most 2 of 3 channels are ever lit per
//   LED, ~40mA/LED worst case). At 150 LEDs, full brightness could draw
//   ~6A. With a 3A supply: 255 x (3 / 6) ~= 127, set a bit lower.
// - MAX_BRIGHTNESS_WHITE: applies at zero saturation (pure white, all 3
//   channels lit, ~60mA/LED worst case). At 150 LEDs, full brightness
//   could draw ~9A. With a 3A supply: 255 x (3 / 9) ~= 85, set a
//   bit lower.
//
// The actual ceiling used is interpolated between these two based on
// the color pot's current saturation, so you only lose brightness
// headroom as you approach white, not across the whole color wheel.
const byte MAX_BRIGHTNESS_COLOR = 127;    //was 110
const byte MAX_BRIGHTNESS_WHITE = 85;     //was 74

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHTNESS_WHITE); // safe default until loop() sets the real ceiling
}

void loop() {
  int colorReading = readSmoothed(COLOR_POT_PIN);
  int brightnessReading = readSmoothed(BRIGHTNESS_POT_PIN);

  // Map the color pot to an extended range: 0-255 sweeps the color wheel
  // (full saturation), and 256-280 fades saturation down to 0, so the
  // very top of the pot's travel lands on pure white.
  int colorExtended = map(colorReading, 0, 1023, 0, 280);
  byte hue;
  byte saturation;
  if (colorExtended <= 255) {
    hue = (byte)colorExtended;
    saturation = 255;
  } else {
    hue = 255; // irrelevant once saturation reaches 0
    saturation = map(colorExtended, 255, 280, 255, 0);
  }

  // Interpolate the brightness ceiling based on how saturated the current
  // color is: full ceiling at full saturation, lower ceiling as it fades
  // toward white.
  byte brightnessCeiling = map(saturation, 0, 255, MAX_BRIGHTNESS_WHITE, MAX_BRIGHTNESS_COLOR);

  // Map the brightness pot (0-1023) to a 0-brightnessCeiling scale.
  // Even with the pot at max, output never exceeds the ceiling above.
  byte brightness = map(brightnessReading, 0, 1023, 0, brightnessCeiling);

  // Set every LED on the strip to the same color
  fill_solid(leds, NUM_LEDS, CHSV(hue, saturation, 255));
  FastLED.setBrightness(brightness);
  FastLED.show();
}

// Reads a pin multiple times and averages it, to smooth pot noise
int readSmoothed(int pin) {
  long total = 0;
  for (int i = 0; i < SMOOTHING_SAMPLES; i++) {
    total += analogRead(pin);
  }
  return total / SMOOTHING_SAMPLES;
}
