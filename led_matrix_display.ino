#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Matrix settings
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define DATA_PIN 11
#define CLK_PIN 13
#define CS_PIN 10

// Create display
MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
MD_MAX72XX* mx = display.getGraphicObject();  // Fixed: pointer instead of reference

// Full 8x8 heart (rows)
uint8_t heartBitmap[8] = {
  B00000000,
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000
};

enum State { SCROLLING, SHOW_HEART };
State currentState = SCROLLING;

void setup() {
  display.begin();
  display.setIntensity(5);
  display.displayClear();

  display.displayText("ROBOCRAZE", PA_LEFT, 100, 1000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop() {
  if (currentState == SCROLLING) {
    if (display.displayAnimate()) {
      currentState = SHOW_HEART;
      display.displayClear();

      // Draw heart on last module (module 3 if you have 4)
      uint8_t moduleIndex = MAX_DEVICES - 1;

      for (uint8_t row = 0; row < 8; row++) {
        mx->setRow(moduleIndex, row, heartBitmap[row]);  // Use -> instead of .
      }

      delay(2000); // Keep heart for 2 seconds

      // Reset text
      display.displayClear();
      display.displayText("ROBOCRAZE", PA_LEFT, 100, 1000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
      currentState = SCROLLING;
    }
  }
}
