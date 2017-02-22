#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Fonts/TomThumb.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include "display.h"
#include "pins.h"
#include "thermocouple.h"

Adafruit_PCD8544 lcd = Adafruit_PCD8544(LCD_DC, LCD_CS, LCD_RST);

int frame = 0;
bool displayNeedsUpdate = false;

void setupDisplay() {
  lcd.begin();
  lcd.clearDisplay();
  lcd.setContrast(40);
}

void displayCurrentTemperature(double temp) {
  lcd.setFont(&FreeSansBold12pt7b);
  lcd.fillRect(0, 7, 84, 20, WHITE);
  lcd.setTextColor(BLACK);
  lcd.setCursor(0, 26);
  lcd.print((int)temp);
  lcd.print((char)0xB0);
  lcd.print("C");
  displayNeedsUpdate = true;
}

void displayTargetTemperature(double temp) {
  lcd.setFont(&FreeSansBold12pt7b);
  lcd.fillRect(0, 28, 84, 20, WHITE);
  lcd.setTextColor(BLACK);
  lcd.setCursor(0, 47);
  lcd.print((int)temp);
  lcd.print((char)0xB0);
  lcd.print("C");
  displayNeedsUpdate = true;
}

void displayStatus(String state) {
  lcd.setFont(&TomThumb);
  lcd.fillRect(0, 0, 75, 7, BLACK);
  lcd.setTextColor(WHITE);
  lcd.setCursor(1, 6);
  if(state)
    lcd.print(state);
  else
    lcd.print(state);
  displayNeedsUpdate = true;
}

void displayRelayState(bool state) {
  lcd.setFont(&TomThumb);
  lcd.fillRect(76, 0, 8, 7, BLACK);
  lcd.setTextColor(WHITE);
  lcd.setCursor(77, 6);
  if(state)
    lcd.print("0");
  else
    lcd.print("1");
  displayNeedsUpdate = true;
}

void loopDisplay() {
  if(displayNeedsUpdate) {
    lcd.display();
    displayNeedsUpdate = false;
  }
}
