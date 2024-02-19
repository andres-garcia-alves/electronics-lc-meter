#include "Definitions.h"
#include "Display_LCD.h"
#include "Measurements.h"

void setup()
{
  setupLCD();
  defaultPinout(true);
  setCapacimeterMode(Med);
  showIntro(2000);
  Serial.begin(9600);
}

void loop()
{
  CapacimeterMode mode = checkInput();

  if (mode != None) {
    setCapacimeterMode(mode);
    showCapacitanceMode();
    defaultPinout(false);
  }

  showCapacitance();
  showInductance();

  delay(50);
}

CapacimeterMode checkInput()
{
  byte value = 0;

  if      (digitalRead(PIN_BTN_CX_LOW) == LOW)   { value = Low; }
  else if (digitalRead(PIN_BTN_CX_MED) == LOW)   { value = Med; }
  else if (digitalRead(PIN_BTN_CX_HIGH) == LOW)  { value = High; }

  delay(75);

  if      (value == Low && digitalRead(PIN_BTN_CX_LOW) == LOW)    { return Low; }
  else if (value == Med && digitalRead(PIN_BTN_CX_MED) == LOW)    { return Med; }
  else if (value == High && digitalRead(PIN_BTN_CX_HIGH) == LOW)  { return High; }
  else                                                            { return None; }
}

void showIntro(unsigned int wait)
{
  printLCD(0, LCD_ROW_0, "    LC Meter    ");
  printLCD(0, LCD_ROW_1, "                ");
  delay(wait);
}

void showCapacitance()
{
  float capacitance = getCapacitance();

  char value[MEASURE_LEN];
  (capacitance < 1000) ? dtostrf(capacitance, MEASURE_LEN, 1, value) : dtostrf(capacitance / 1000.0, MEASURE_LEN, 1, value);
  String unit = (capacitance < 1000) ? " nF" : " uF";

  printLCD(0, LCD_ROW_0, "Cap.: " + (String)value + unit);
}

void showInductance()
{
  float inductance = getInductance();

  char value[MEASURE_LEN];
  dtostrf(inductance, MEASURE_LEN, 1, value);

  printLCD(0, LCD_ROW_1, "Ind.: " + (String)value + " uH");
}
