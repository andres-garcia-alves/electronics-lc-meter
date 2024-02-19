#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

struct CapacitanceParams {
  char description[16] = "";
  byte chargeCapacitorPin = 0;
  float chargeResistanceValue = 0;
  float parasiticCapacitance = 0;
} params;


CapacitanceParams setCapacimeterMode(CapacimeterMode mode)
{
  if (mode == Low) {
    strcpy(params.description, "> accuracy mode ");
    params.chargeCapacitorPin = PIN_CAPACITOR_CHARGE_LOW;
    params.chargeResistanceValue = CX_RESISTOR_LOW;
    params.parasiticCapacitance = CX_PARASITIC_LOW;
  }
  else if (mode == Med) {
    strcpy(params.description, "> balanced mode ");
    params.chargeCapacitorPin = PIN_CAPACITOR_CHARGE_MED;
    params.chargeResistanceValue = CX_RESISTOR_MED;
    params.parasiticCapacitance = CX_PARASITIC_MED;
  }
  else if (mode == High) {
    strcpy(params.description, "> speed mode    ");
    params.chargeCapacitorPin = PIN_CAPACITOR_CHARGE_HIGH;
    params.chargeResistanceValue = CX_RESISTOR_HIGH;
    params.parasiticCapacitance = CX_PARASITIC_HIGH;
  }
}

void showCapacitanceMode() {
  printLCD(0, LCD_ROW_0, params.description);
  delay(1000);
}

float getCapacitance()
{
  // charging phase
  pinMode(params.chargeCapacitorPin, OUTPUT);
  digitalWrite(params.chargeCapacitorPin, HIGH);
  
  unsigned long startTime = micros();
  while (analogRead(PIN_CAPACITOR_MEASURE) < 645) { }
  unsigned long elapsedTime = micros() - startTime;

  float Cx = ((float)elapsedTime / params.chargeResistanceValue) * 1000.0;   // ToDo: si es necesario el multiplicar x 1000
  Cx -= params.parasiticCapacitance;
  digitalWrite(params.chargeCapacitorPin, LOW);

  // discharging phase
  pinMode(PIN_CAPACITOR_DISCHARGE, OUTPUT);
  digitalWrite(PIN_CAPACITOR_DISCHARGE, LOW);
  while (analogRead(PIN_CAPACITOR_MEASURE) > 10) { }  // ToDo: revisar, x margen de error (no descarga hasta cero) !!

  // clean-up phase
  pinMode(params.chargeCapacitorPin, INPUT);                 // ToDo: revisar, tal vez innecesario
  pinMode(PIN_CAPACITOR_DISCHARGE, INPUT);

  return Cx;
}

float getInductance()
{
  pinMode(PIN_INDUCTANCE_OUT, OUTPUT);
  digitalWrite(PIN_INDUCTANCE_OUT, HIGH);

  delay(1);
  pinMode(PIN_INDUCTANCE_OUT, INPUT);                 // ToDo: revisar, tal vez innecesario
  digitalWrite(PIN_INDUCTANCE_OUT, LOW);
  
  unsigned long t = pulseIn(PIN_INDUCTANCE_IN, LOW);

  float fo = 1000000 / (t * 2);
  float Lx = (1 / (4 * pow(PI, 2) * pow(fo, 2) * LX_CAPACITOR)) * 1000000;

  return Lx;
}

#endif
