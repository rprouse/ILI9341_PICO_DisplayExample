#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "ili9341.h"
#include "gfx.h"
#include "DisplayTest.h"

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

void InitializeDisplay()
{
    // Initialize display
    puts("Initializing display...");
    LCD_setPins(TFT_DC, TFT_CS, TFT_RST, TFT_SCLK, TFT_MOSI);
    LCD_initDisplay();
    LCD_setRotation(TFT_ROTATION);
    GFX_createFramebuf();
    GFX_setClearColor(BACKGROUND);
    GFX_setTextBack(BACKGROUND);
    GFX_setTextColor(FOREGROUND);
    GFX_clearScreen();
}

void Commodore64()
{
    // Initialize GFX
    puts("Initializing graphics...");
    GFX_fillRect(MARGIN * 2, MARGIN, GFX_getWidth() - MARGIN * 4, GFX_getHeight() - MARGIN * 2, BACKGROUND);
    GFX_flush();

    // Draw some text
    puts("Writing...");
    printLine(INDENT * 2, INDENT, "    **** COMMODORE 64 BASIC V2 ****");
    printLine(INDENT * 2, INDENT + LINE_HEIGHT, " 64K RAM SYSTEM  38911 BASIC BYTES FREE");
    printLine(INDENT * 2, INDENT + 2 * LINE_HEIGHT, "READY.");

    while (true)
    {
      puts("Ping...");
      GFX_fillRect(INDENT * 2, INDENT + 3 * LINE_HEIGHT, 6, 8, BACKGROUND);
      GFX_flush();
      sleep_ms(500);

      GFX_fillRect(INDENT * 2, INDENT + 3 * LINE_HEIGHT, 6, 8, FOREGROUND);
      GFX_flush();
      sleep_ms(500);
    }
}

void Terminal()
{
    int currentLine = 0;

    int w = GFX_getWidth();
    int h = GFX_getHeight();

    GFX_printf("Screen size: %d x %d\n", w, h);
    currentLine++;
    GFX_flush();

    for (int i = 1; i < 50; i++)
    {
      currentLine++;
      if (currentLine * LINE_HEIGHT > h)
      {
        GFX_scrollUp(LINE_HEIGHT);
        GFX_setCursor(0, h - LINE_HEIGHT);
        currentLine--;
      }
      GFX_printf("Line %d\n", i);
      GFX_flush();
      sleep_ms(DELAY);
    }
}

int main()
{
    stdio_init_all();

    InitializeDisplay();
    //Commodore64();
    Terminal();

    return 0;
}
