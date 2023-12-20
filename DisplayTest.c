#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "ili9341.h"
#include "gfx.h"
#include "DisplayTest.h"

// Display the Commodore 64 screen or the Terminal
#define COMMODORE64 1

int main()
{
    stdio_init_all();

#ifdef COMMODORE64
    InitializeDisplay(FOREGROUND);
    Commodore64();
#else
    InitializeDisplay(BACKGROUND);
    Terminal();
#endif

    return 0;
}

void printLine(uint16_t line, const char *str)
{
    int len = strlen(str);
    GFX_setCursor(INDENT * 2, INDENT + line * LINE_HEIGHT);
    GFX_printf(str);
    GFX_flush();
}

void InitializeDisplay(uint16_t color)
{
    // Initialize display
    puts("Initializing display...");
    LCD_setPins(TFT_DC, TFT_CS, TFT_RST, TFT_SCLK, TFT_MOSI);
    LCD_initDisplay();
    LCD_setRotation(TFT_ROTATION);
    GFX_createFramebuf();
    GFX_setClearColor(color);
    GFX_setTextBack(BACKGROUND);
    GFX_setTextColor(FOREGROUND);
    GFX_clearScreen();
}

// This displays a fake Commodore 64 screen
void Commodore64()
{
    // Initialize GFX
    puts("Initializing graphics...");
    GFX_fillRect(MARGIN * 2, MARGIN, GFX_getWidth() - MARGIN * 4, GFX_getHeight() - MARGIN * 2, BACKGROUND);
    GFX_flush();

    // Draw some text
    puts("Writing...");
    uint16_t line = 0;
    printLine(line++, "    **** COMMODORE 64 BASIC V2 ****");
    printLine(line++, " 64K RAM SYSTEM  38911 BASIC BYTES FREE");
    printLine(line++, "READY.");
    printLine(line++, "LOAD\"*\",8,1");
    printLine(line++, "SEARCHING FOR *");
    printLine(line++, "LOADING");
    printLine(line++, "READY.");
    printLine(line++, "RUN");
    printLine(line++, "HELLO WORLD");

    while (true)
    {
        puts("Ping...");
        GFX_fillRect(INDENT * 2, INDENT + line * LINE_HEIGHT, 6, 8, BACKGROUND);
        GFX_flush();
        sleep_ms(500);

        GFX_fillRect(INDENT * 2, INDENT + line * LINE_HEIGHT, 6, 8, FOREGROUND);
        GFX_flush();
        sleep_ms(500);
    }
}

// This displays a scrolling terminal
void Terminal()
{
    int currentLine = 0;

    int w = GFX_getWidth();
    int h = GFX_getHeight();

    GFX_printf("Screen size: %d x %d\n", w, h);
    currentLine++;
    GFX_flush();

    for (int i = 1; i < 32; i++)
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
