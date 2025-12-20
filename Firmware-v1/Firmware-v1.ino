#include <Wire.h>               // comunicacion I2C
#include <LiquidCrystal_I2C.h>  // pantalla LCD I2C

#define PIN_CAPACITOR_CHARGE_1    11
#define PIN_CAPACITOR_CHARGE_2    10
#define PIN_CAPACITOR_CHARGE_3     9
#define PIN_CAPACITOR_DISCHARGE    8
#define PIN_CAPACITOR_MEASURE     A0
#define PIN_INDUCTANCE_OUT  6
#define PIN_INDUCTANCE_IN   5

#define CX_RESISTOR_1       10060.0     // Cx measure, load resistor 1 (Ohms)
#define CX_RESISTOR_2       099550.0    // Cx measure, load resistor 2 (Ohms)
#define CX_RESISTOR_3       1017000.0   // Cx measure, load resistor 3 (Ohms)
#define LX_CAPACITOR        0.000001000 // Lx measure, parallel capacitor (nF)

#define LCD_ROW_1           0
#define LCD_ROW_2           1

// LCD connections via I2C, address 0x27, SDA -> pin A4, SCL -> pin A5
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // address, #columns, #row

void setup()
{
  pinMode(PIN_INDUCTANCE_OUT, OUTPUT);
  pinMode(PIN_INDUCTANCE_IN, INPUT);
  pinMode(PIN_CAPACITOR_CHARGE_1, OUTPUT);
  // pinMode(cargaCap2, OUTPUT);
  // pinMode(cargaCap3, OUTPUT);
  pinMode(PIN_CAPACITOR_DISCHARGE, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  showIntro();
}

void loop()
{
  showCapacitance();
  showInductance();
}


void showIntro()
{
  lcd.setCursor(0, LCD_ROW_1);
  lcd.print("    LC Meter    ");
  lcd.setCursor(0, LCD_ROW_2);
  lcd.print("                ");
  delay(2000);

  lcd.setCursor(0, LCD_ROW_1);
  lcd.print("loading ...     ");
  lcd.setCursor(0, LCD_ROW_2);
  lcd.print("                ");
}

void showCapacitance()
{
  float capacitance = getCapacitance();

  char value[7];
  (capacitance < 1000) ? dtostrf(capacitance, 7, 1, value) : dtostrf(capacitance / 1000.0, 7, 1, value);
  String unit = (capacitance < 1000) ? " nF" : " uF";

  lcd.setCursor(0, LCD_ROW_1);
  lcd.print("Cap.: " + (String)value + unit);
}

void showInductance()
{
  float inductance = getInductance();

  char value[7];
  dtostrf(inductance, 7, 1, value);

  lcd.setCursor(0, LCD_ROW_2);
  lcd.print("Ind.: " + (String)value + " uH");
}

float getCapacitance()
{
  pinMode(PIN_CAPACITOR_CHARGE_1, OUTPUT);
  digitalWrite(PIN_CAPACITOR_CHARGE_1, HIGH);

  unsigned long startTime = micros();
  while(analogRead(PIN_CAPACITOR_MEASURE) < 645) { }
  unsigned long elapsedTime = micros() - startTime;

  float Cx = ((float)elapsedTime / CX_RESISTOR_1) * 1000.0;

  digitalWrite(PIN_CAPACITOR_CHARGE_1, LOW);
  pinMode(PIN_CAPACITOR_DISCHARGE, OUTPUT);
  digitalWrite(PIN_CAPACITOR_DISCHARGE, LOW);

  while(analogRead(PIN_CAPACITOR_MEASURE) > 10) { }
  pinMode(PIN_CAPACITOR_DISCHARGE, INPUT);

  return Cx;
}

float getInductance()
{
  digitalWrite(PIN_INDUCTANCE_OUT, HIGH);
  delay(1);
  digitalWrite(PIN_INDUCTANCE_OUT, LOW);
  
  unsigned long t = pulseIn(PIN_INDUCTANCE_IN, LOW);
  float fo = 1000000 / (t * 2);
  float Lx = (1 / (4 * pow(PI, 2) * pow(fo, 2) * LX_CAPACITOR)) * 1000000;

  return Lx;
}
