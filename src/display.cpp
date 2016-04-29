#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "display.h"
#include "pins.h"

Adafruit_PCD8544 lcd = Adafruit_PCD8544(LCD_DC, LCD_CS, LCD_RST);

void setupDisplay() {
  lcd.begin();
  lcd.clearDisplay();
  lcd.setCursor(0, 0);
  lcd.setTextSize(1);
  lcd.println("Current:");
  lcd.setCursor(0, 3 * 8);
  lcd.println("Target:");
}

void displayCurrentTemperature(double temp) {
  lcd.drawRect(0, 9, 84, 16, WHITE);
  lcd.setCursor(0, 9);
  lcd.setTextSize(2);
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C");
}

void displayTargetTemperature(double temp) {
  lcd.drawRect(0, 26, 84, 16, WHITE);
  lcd.setCursor(0, 26);
  lcd.setTextSize(2);
  lcd.print(temp, DEC);
  lcd.print((char)223);
  lcd.print("C");
}

void displayRelayState(bool state) {
  lcd.setTextSize(1);
  lcd.drawRect(73, 0, 11, 9, WHITE);
  lcd.setCursor(73, 0);
  if (state)
    lcd.print(" ON");
  else
    lcd.print("OFF");
}
