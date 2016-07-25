#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "display.h"
#include "pins.h"
#include "thermocouple.h"

Adafruit_PCD8544 lcd = Adafruit_PCD8544(LCD_DC, LCD_CS, LCD_RST);

int frame = 0;

void setupDisplay() {
  lcd.begin();
  lcd.clearDisplay();
  lcd.setContrast(40);
  lcd.display();
}

void displayCurrentTemperature(double temp) {
  lcd.fillRect(0, 9, 84, 16, WHITE);
  lcd.setCursor(0, 9);
  lcd.setTextSize(2);
  lcd.print((int)temp);
  lcd.print("C");
  lcd.display();
}

void displayTargetTemperature(double temp) {
  lcd.fillRect(0, 26, 84, 16, WHITE);
  lcd.setCursor(0, 26);
  lcd.setTextSize(2);
  lcd.print((int)temp);
  lcd.print("C");
  lcd.display();
}

void displayRelayState(bool state) {
  lcd.setTextSize(1);
  lcd.fillRect(73, 0, 11, 9, WHITE);
  lcd.setCursor(73, 0);
  if (state)
    lcd.print(" ON");
  else
    lcd.print("OFF");
  lcd.display();
}
