#ifndef DISPLAY_LCD_H
#define DISPLAY_LCD_H

#include <Wire.h>               // I2C communication
#include <LiquidCrystal_I2C.h>  // I2C LCD display

// LCD connections via I2C, address 0x27, SDA -> pin A4, SCL -> pin A5
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // params: address, #columns, #row

void setupLCD()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void printLCD(byte column, byte row, String text)
{
  lcd.setCursor(column, row);
  lcd.print(text);
}

#endif
