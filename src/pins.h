#ifndef _PINS_H
#define _PINS_H

#define SPI_CLK 13
#define SPI_MISO 12
#define SPI_MOSI 11

#define THERMOCOUPLE_CS 14

#define LCD_CS 9
#define LCD_RST 8
#define LCD_DC 10

#define ENCODER_A 2
#define ENCODER_B 1
#define ENCODER_BTN 3

#define RELAY 0

void setupPins();

#endif
