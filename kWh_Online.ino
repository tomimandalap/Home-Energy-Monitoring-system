#include "EmonLib.h"
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

EnergyMonitor emon1;
SoftwareSerial nodemcu(2, 3); //rx, tx
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

//variabel data
int sdata1 = 0; //data tegangan
float sdata2 = 0; //data arus
int sdata3 = 0; //data daya
float sdata4 = 0; //data power factor
String cdata;
float Vac, I;

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(115200);
  nodemcu.begin(115200);


  emon1.voltage(0, 361.26, 1.7); //tegangan A0
  emon1.current(1, 40); //arus A1

  lcd.setCursor(3, 0);
  lcd.print("kWh Online");
  lcd.setCursor(0, 1);
  lcd.print("duino elektronik");
  delay(3000);
  lcd.clear();
}

void loop()
{
  static unsigned long timepoint = millis();
  if (millis() - timepoint > 2000U)
  {
    timepoint = millis();
    
    emon1.calcVI(120, 2000);

    int apparentPower = emon1.apparentPower; //daya
    float powerFActor = abs(emon1.powerFactor);
    Vac = emon1.Vrms;
    I = emon1.Irms;
    
    sdata1 = Vac;
    sdata2 = I;
    sdata3 = apparentPower;
    sdata4 = powerFActor;

    cdata = cdata + sdata1 + "," + sdata2 + "," + sdata3 + "," + sdata4;
    nodemcu.println(cdata);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T : ");
    lcd.print(Vac, 0);
    lcd.setCursor(9, 0);
    lcd.print("V");

    lcd.setCursor(0, 1);
    lcd.print("I : ");
    lcd.print(I);
    lcd.setCursor(9, 1);
    lcd.print("A");

    lcd.setCursor(12, 0);
    lcd.print("DAYA");
    lcd.setCursor(12, 1);
    lcd.print(apparentPower);
    lcd.setCursor(15, 1);
    lcd.print("W");
    
    cdata = "";
  }
}
