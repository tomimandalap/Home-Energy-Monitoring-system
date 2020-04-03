#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
char auth[] = "pAKNLvno1w1-o-0eFGED10YBjxDpzzcE";
char ssid[] = "duinoelektronik";
char pass[] = "atmega88p";
BlynkTimer timer;

char rdata;
float data2, data4;
int data1, data3;
String myString;

void myTimerEvent()
{
  baca();
  Blynk.virtualWrite(V1, data1);
  Blynk.virtualWrite(V2, data2);
  Blynk.virtualWrite(V3, data3);
  Blynk.virtualWrite(V4, data4);
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.en-26.com", 9600);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  baca();
}

void baca()
{
  if (Serial.available() > 0 )
  {
    rdata = Serial.read();
    myString = myString + rdata;
    // Serial.print(rdata);
    if ( rdata == '\n')
    {
      String l = getValue(myString, ',', 0);
      String m = getValue(myString, ',', 1);
      String n = getValue(myString, ',', 2);
      String o = getValue(myString, ',', 3);

      data1 = l.toInt();
      data2 = m.toFloat();
      data3 = n.toInt();
      data4 = o.toFloat();
      
      Serial.print("Tegangan : ");
      Serial.println(data1);
      Serial.print("Arus : ");
      Serial.println(data2);
      Serial.print("Daya : ");
      Serial.println(data3);
      Serial.print("P. Factor : ");
      Serial.println(data4,1);
      Serial.print("\n");
      myString = "";
    }
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
