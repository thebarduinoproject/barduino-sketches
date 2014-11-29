#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress outsideThermometer = { 0x28, 0xB0, 0x29, 0x30, 0x05, 0x00, 0x00, 0x6F };
DeviceAddress insideThermometer = { 0x28, 0x93, 0x6C, 0x2F, 0x05, 0x00, 0x00, 0x19 };

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  sensors.setResolution(insideThermometer, 10);
  sensors.setResolution(outsideThermometer, 10);
  lcd.begin(16, 2);
}

void printTemperature(DeviceAddress deviceAddress)
{
  int tempF = 0;
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127.00) {
    Serial.print("Error getting temperature");
  } else {
    tempF = (int) ((tempC * 1.8) + 32 + 0.5);
    lcd.print(tempF);
    lcd.print((char)223);
    lcd.print("F");
  }
}

void loop(void)
{ 
  delay(30000); // 2 min
  sensors.requestTemperatures();
  lcd.setCursor(0, 0);
  lcd.print("InTemp: ");
  printTemperature(insideThermometer);
  lcd.setCursor(0, 1);
  lcd.print("OutTemp: ");
  printTemperature(outsideThermometer);
}
