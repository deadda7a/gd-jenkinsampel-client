#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>
#include <TM1650.h>
#include <Wire.h>

TM1650 Disp4Seg;
// #define SDA_pin 20
// #define SCL_pin 21
StaticJsonBuffer<200> jsonBuffer;
char endMarker = '\n';
int status = 0;
int price = 0;
bool building = false;
bool jourfix = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000);
  Disp4Seg.Init();
  delay(1000);
  Serial.println("Arduino ready");
}

String getJsonRaw() {
  String receivedChars = "";
  receivedChars = Serial.readStringUntil(endMarker);
  return receivedChars;
}

void displayPrice(int price) {
  Disp4Seg.SetBrightness(1);
  Disp4Seg.SetDot(1, true);
  Disp4Seg.WriteNum(price);
  delay(5);
  Disp4Seg.DisplayOFF();
}

void loop() {
  if (Serial.available() > 0) {
    char op = char(Serial.readStringUntil(endMarker)[0]);

    switch (op) {
    case 'r': {
      Serial.print("send\n");

    } break;

    case 'w': {
      Serial.print("recv\n");
      String jsonString = getJsonRaw();

      int count = jsonString.length();
      char testArray[count];

      jsonString.toCharArray(testArray, count);

      JsonObject &root = jsonBuffer.parseObject(jsonString);

      if (!root.success()) {
        Serial.println("parseObject failed");
      } else {
        price = root["price"];
        building = root["building"];
        jourfix = root["jourfix"];
        status = root["status"];

        displayPrice(price);
      }
    } break;

    default:
      Serial.print("What the fuck?\n");
      break;
    }
  }
}
