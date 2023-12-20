#ifndef __DISPLAYTEST_H__
#define __DISPLAYTEST_H__

#define PICO_BREADBOARD_KIT 1

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
#define USE_SD_CARD     1
#define TFT_SCLK        18
#define TFT_MOSI        19
#define TFT_MISO        255 // Not required, used for DC...
#define TFT_DC          16
#define TFT_RST         21
#define TFT_CS          17
#define TFT_BACKLIGHT   255 // hardwired to 3.3v
#endif

#define TFT_WIDTH       320
#define TFT_HEIGHT      240
#define TFT_ROTATION    3

// Pin definitions for the SD card
#define SD_SCLK         10
#define SD_MOSI         11
#define SD_MISO         12
#define SD_CS           13

#define MARGIN 16
#define INDENT (MARGIN + 4)
#define LINE_HEIGHT 8
#define DELAY 5

// Colors are in 565 (FFFF) format. To convert from RGB888 to RGB565, use:
//   ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
#define BACKGROUND 0x1052
#define FOREGROUND 0x73BF

#endif