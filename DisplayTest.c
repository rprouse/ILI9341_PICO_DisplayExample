#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "lib/ili9341/ili9341.h"
#include "lib/gfx/gfx.h"

#define MARGIN 16
#define INDENT (MARGIN + 4)
#define LINE_HEIGHT 10
#define DELAY 10
#define BACKGROUND ILI9341_BLUE
#define FOREGROUND ILI9341_CYAN

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
    LCD_setPins(15, 13, 14, 6, 7);
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
