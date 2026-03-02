#include <Arduino.h>
#include <Arduino_GFX_Library.h>

#define TFT_BL 21
Arduino_DataBus *bus = new Arduino_ESP32SPI(2 /* DC */, 15 /* CS */, 14 /* SCK */, 13 /* MOSI */, 12 /* MISO */);
Arduino_GFX *gfx = new Arduino_ILI9341(bus, GFX_NOT_DEFINED /* RST */, 0 /* rotation */);

uint32_t screenWidth = 320;
uint32_t screenHeight = 240;

void setup() {
  Serial.begin(115200);

  gfx->begin();  // Init Display
  gfx->setRotation(3);
  gfx->fillScreen(BLACK);

  #ifdef TFT_BL
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
  #endif

  gfx->setTextSize(2);

  gfx->setCursor(10, 10);
  gfx->setTextColor(RED);
  gfx->println("Hello World - RED");

  gfx->setCursor(10, 30);
  gfx->setTextColor(GREEN);
  gfx->println("Hello World - GREEN");

  gfx->setCursor(10, 50);
  gfx->setTextColor(BLUE);
  gfx->println("Hello World - BLUE");
}

void loop() {

}