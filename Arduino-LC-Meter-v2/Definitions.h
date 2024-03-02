#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define PIN_BTN_CX_LOW      2
#define PIN_BTN_CX_MED      3
#define PIN_BTN_CX_HIGH     4

#define PIN_CAPACITOR_CHARGE_LOW    9
#define PIN_CAPACITOR_CHARGE_MED    10
#define PIN_CAPACITOR_CHARGE_HIGH   11
#define PIN_CAPACITOR_DISCHARGE     8
#define PIN_CAPACITOR_MEASURE       A0

#define PIN_INDUCTANCE_OUT  6
#define PIN_INDUCTANCE_IN   5

#define CX_RESISTOR_LOW     1017000.0   // Cx measure, load resistor 3 (Ohms)
#define CX_RESISTOR_MED     0099550.0   // Cx measure, load resistor 2 (Ohms)
#define CX_RESISTOR_HIGH    0010060.0   // Cx measure, load resistor 1 (Ohms)
#define CX_PARASITIC_LOW    00.2        // Cx parasitic capacity, accuracy mode
#define CX_PARASITIC_MED    01.1        // Cx parasitic capacity, balanced mode
#define CX_PARASITIC_HIGH   11.1        // Cx parasitic capacity, speed mode
#define LX_CAPACITOR        0.000001000 // Lx measure, parallel capacitor (nF)

#define LCD_ROW_0           0
#define LCD_ROW_1           1
#define MEASURE_LEN         7

#define DEBUG               false

// capacimeter mode: 1 = Low (pF), 2 = Med (nF), 3 = High (uF)
enum CapacimeterMode { None, Low, Med, High };


void defaultPinout(bool includeButtons)
{
  if (includeButtons) {
    pinMode(PIN_BTN_CX_LOW, INPUT_PULLUP);
    pinMode(PIN_BTN_CX_MED, INPUT_PULLUP);
    pinMode(PIN_BTN_CX_HIGH, INPUT_PULLUP);
  }

  // all pins to high-impedance
  pinMode(PIN_CAPACITOR_CHARGE_LOW, INPUT);
  pinMode(PIN_CAPACITOR_CHARGE_MED, INPUT);
  pinMode(PIN_CAPACITOR_CHARGE_HIGH, INPUT);
  pinMode(PIN_CAPACITOR_DISCHARGE, INPUT);
  pinMode(PIN_CAPACITOR_MEASURE, INPUT);

  pinMode(PIN_INDUCTANCE_OUT, INPUT);
  pinMode(PIN_INDUCTANCE_IN, INPUT);
}

#endif
