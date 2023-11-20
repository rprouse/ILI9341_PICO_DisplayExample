#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "lib/ili9341/ili9341.h"
#include "lib/gfx/gfx.h"

//#define PICO_BREADBOARD_KIT 1

// Pin definitions for the LCD
#ifdef PICO_BREADBOARD_KIT
#define TFT_SCLK        6
#define TFT_MOSI        7
#define TFT_MISO        255 // Not required, used for DC...
#define TFT_DC          15
#define TFT_RST         14
#define TFT_CS          13
#define TFT_BACKLIGHT   255 // hardwired to 3.3v
#else
#define TFT_SCLK        18
#define TFT_MOSI        19
#define TFT_MISO        255 // Not required, used for DC...
#define TFT_DC          16
#define TFT_RST         21
#define TFT_CS          17
#define TFT_BACKLIGHT   255 // hardwired to 3.3v
#endif

#define MARGIN 16
#define INDENT (MARGIN + 4)
#define LINE_HEIGHT 10
#define DELAY 10

// Colors are in 565 (FFFF) format. To convert from RGB888 to RGB565, use:
//   ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
#define BACKGROUND 0x1052
#define FOREGROUND 0x73BF

void printLine(uint16_t x, uint16_t y, const char *line)
{
    int len = strlen(line);
    GFX_setCursor(x, y);
    for (int i = 0; i < len; i++)
    {
      GFX_write(line[i]);
      GFX_flush();
      sleep_ms(DELAY);
    }
}

int main()
{
    stdio_init_all();

    // Initialize display
    puts("Initializing display...");
    LCD_setPins(TFT_DC, TFT_CS, TFT_RST, TFT_SCLK, TFT_MOSI);
    LCD_initDisplay();
    LCD_setRotation(3);

    // Initialize GFX
    puts("Initializing graphics...");
    GFX_createFramebuf();
    GFX_setClearColor(FOREGROUND);
    GFX_clearScreen();
    GFX_fillRect(MARGIN * 2, MARGIN, GFX_getWidth() - MARGIN * 4, GFX_getHeight() - MARGIN * 2, BACKGROUND);
    GFX_setTextColor(FOREGROUND);
    GFX_setTextBack(BACKGROUND);
    GFX_flush();

    // Draw some text
    puts("Writing...");
    printLine(INDENT * 2, INDENT, "    **** COMMODORE 64 BASIC V2 ****");
    printLine(INDENT * 2, INDENT + LINE_HEIGHT, " 64K RAM SYSTEM  38911 BASIC BYTES FREE");
    printLine(INDENT * 2, INDENT + 2 * LINE_HEIGHT, "READY.");

    while (true)
    {
      puts("Ping...");
      sleep_ms(1000);
      puts("Pong...");
      sleep_ms(1000);
    }

    return 0;
}
