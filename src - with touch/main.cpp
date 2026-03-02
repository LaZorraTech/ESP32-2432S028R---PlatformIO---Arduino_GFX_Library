#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <XPT2046_Touchscreen.h>

#define TFT_BL 21
Arduino_DataBus *bus = new Arduino_ESP32SPI(2 /* DC */, 15 /* CS */, 14 /* SCK */, 13 /* MOSI */, 12 /* MISO */);
Arduino_GFX *gfx = new Arduino_ILI9341(bus, GFX_NOT_DEFINED /* RST */, 0 /* rotation */);

uint32_t screenWidth = 320;
uint32_t screenHeight = 240;

// Touchscreen pins
#define XPT2046_IRQ 36  // T_IRQ
#define XPT2046_MOSI 32 // T_DIN
#define XPT2046_MISO 39 // T_OUT
#define XPT2046_CLK 25  // T_CLK
#define XPT2046_CS 33   // T_CS

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

void touchscreen_read() // Get the Touchscreen data
{
    // Get Touchscreen points
        TS_Point p = touchscreen.getPoint();
        // Calibrate Touchscreen points with map function to the correct width and height
        x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
        y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
        z = p.z;

        // Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor
        //Serial.print("X = ");
        //Serial.print(x);
        //Serial.print(" | Y = ");
        //Serial.print(y);
        //Serial.print(" | Pressure = ");
        //Serial.print(z);
        //Serial.println();

        gfx->setCursor(20, 70);
        gfx->print("p.x = ");
        gfx->print(p.x); gfx->print("    ");
        gfx->setCursor(20, 90);
        gfx->print("p.y = ");
        gfx->print(p.y); gfx->print("    ");

        gfx->setCursor(20, 130);
        gfx->print("X = ");
        gfx->print(x); gfx->print("    ");
        gfx->setCursor(20, 150);
        gfx->print("Y = ");
        gfx->print(y); gfx->print("    ");
        gfx->setCursor(20, 170);
        gfx->print("Pressure = ");
        gfx->print(z); gfx->print("    ");
}



void setup() {
  Serial.begin(115200);

  gfx->begin();  // Init Display
  gfx->setRotation(3);
  gfx->fillScreen(BLACK);

  #ifdef TFT_BL
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
  #endif

    // Start the SPI for the touchscreen and init the touchscreen
    touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchscreenSPI);
    // Set the Touchscreen rotation in landscape mode
    // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 1: touchscreen.setRotation(1);
    touchscreen.setRotation(3);

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

  gfx->setTextColor(WHITE,BLACK);
}

void loop() {
  if (touchscreen.tirqTouched() && touchscreen.touched())
    {touchscreen_read();}
}