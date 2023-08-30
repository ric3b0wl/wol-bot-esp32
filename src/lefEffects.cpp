#include "ledEffects.h"

void allOff() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black; // Turn off LED
  }
  FastLED.show(); // Update LEDs to turn them off
}

void bootUpEffect() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
        FastLED.show();
        delay(100); // Adjust the delay time to your preference
    }

    // Turn off LEDs one by one
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
        FastLED.show();
        delay(100); // Adjust the delay time to your preference
    }

    delay(100);

    for (int cycle = 0; cycle < 1; cycle++) {
        for (int blink = 0; blink < 2; blink++) { // Blink twice
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i] = CRGB::White; // Turn on LED with its color
            }
           
            FastLED.show();
            delay(100); // Adjust the delay time to control the blink speed

            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i] = CRGB::Black; // Turn off LED
            }
            FastLED.show();
            delay(100); // Adjust the delay time between blinks
        }
    }

    // Delay before the next cycle
    // delay(100); // Adjust the delay time between cycles to your preference

    allOff();
}

void wolActiveEffect() {
    CRGB colors[] = {CRGB::Red, CRGB::Green, CRGB::Blue}; // Define colors for each LED

    for (int cycle = 0; cycle < 3; cycle++) {
        // Turn on LEDs one by one with different colors
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = colors[i];
            FastLED.show();
            delay(50); // Adjust the delay time to your preference
        }

        // Turn off LEDs one by one
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = CRGB::Black;
            FastLED.show();
            delay(50); // Adjust the delay time to your preference
        }

        // Delay before the next cycle
        // delay(100); // Adjust the delay time between cycles to your preference
    }

    allOff();
}

void colorChaseEffect() {
    CRGB colors[] = {CRGB::Red, CRGB::Green, CRGB::Blue}; // Define colors for each LED

    for (int cycle = 0; cycle < 4; cycle++) { // Number of cycles
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = colors[i]; // Turn on the current LED
            FastLED.show();
            delay(50); // Adjust the delay time to your preference
            leds[i] = CRGB::Black; // Turn off the current LED
        }

        // Delay before the next cycle
        // delay(100); // Adjust the delay time between cycles to your preference
    }

    allOff();
}

void breathingEffect() {
    int brightness = 0;
    int increment = 5;

    for (int cycle = 0; cycle < 4; cycle++) { // Number of cycles
        while (brightness <= 255) {
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = CRGB(brightness, 0, 0); // Set brightness for all LEDs
        }
        FastLED.show();
        delay(20); // Adjust the delay time to control the breathing speed
        brightness += increment;
        }
        
        while (brightness >= 0) {
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = CRGB(brightness, 0, 0); // Set brightness for all LEDs
        }
        FastLED.show();
        delay(20); // Adjust the delay time to control the breathing speed
        brightness -= increment;
        }

        // Delay before the next cycle
        // delay(100); // Adjust the delay time between cycles to your preference
    }
    
    allOff();
}

void knightRiderEffect() {
    int eyeSize = 3; // Number of LEDs in the "eye"

    for (int cycle = 0; cycle < 4; cycle++) { // Number of cycles
        for (int i = 0; i < NUM_LEDS - eyeSize + 1; i++) {
            // Turn on the "eye"
            for (int j = 0; j < eyeSize; j++) {
                leds[i + j] = CRGB::Red;
            }

        FastLED.show();
        delay(50); // Adjust the delay time to your preference

        // Turn off the "eye"
        for (int j = 0; j < eyeSize; j++) {
            leds[i + j] = CRGB::Black;
            }
        }

        // Backward sweep
        for (int i = NUM_LEDS - eyeSize; i >= 0; i--) {
            // Turn on the "eye"
            for (int j = 0; j < eyeSize; j++) {
                leds[i + j] = CRGB::Red;
            }

            FastLED.show();
            delay(50); // Adjust the delay time to your preference

            // Turn off the "eye"
            for (int j = 0; j < eyeSize; j++) {
                leds[i + j] = CRGB::Black;
            }
        }

        // Delay before the next cycle
        // delay(100); // Adjust the delay time between cycles to your preference
    }

    allOff();
}

void rainbowEffect() {
  int numColors = 30; // Number of different colors in the rainbow
  int hueIncrement = 256 / numColors; // Increment to change hue

  for (int cycle = 0; cycle < 3; cycle++) {
    for (int hue = 0; hue < 256; hue += hueIncrement) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue + (i * hueIncrement), 255, 255);
      }
      FastLED.show();
      delay(50); // Adjust the delay time to your preference
    }

    // Delay before the next cycle
    // delay(300); // Adjust the delay time between cycles to your preference
  }
  
  allOff();
}
