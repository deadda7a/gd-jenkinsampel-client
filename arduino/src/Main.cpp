#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>
#include <string.h>

StaticJsonBuffer<200> jsonBuffer;
String state = "off";
float price = 0;

String recvData() {
  String endMarker = "\n";
  String rc = "";
  String receivedChars = "";

  while (Serial.available() > 0) {
    rc = Serial.readString();

    if (rc != endMarker) {
      receivedChars += rc;
    } else {
      return receivedChars;
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial.print("Arduino ready");
}

void loop() {
  String endMarker = "\n";

  if (Serial.available() > 0) {
    String rc = "";
    // char receivedChars[numChars];
    String receivedChars = "";

    rc = Serial.readString();

    if (rc != endMarker) {
      receivedChars += rc;
    } else {
      Serial.print(receivedChars);
    }

    // char op = char(Serial.read());
    //
    // switch (op) {
    // case 'r': {
    //   Serial.print("send\n");
    //
    // } break;
    // case 'w': {
    //   Serial.print("recv\n");
    //   String json = recvData();
    //   Serial.print("recv1\n");
    //   JsonObject &root = jsonBuffer.parseObject(json);
    //   Serial.print("recv2\n");
    //   if (!root.success()) {
    //     Serial.println("parseObject() failed");
    //     return;
    //   }
    //   Serial.print("recv3\n");
    //   state = root["state"].as<String>();
    //   price = root["price"];
    // } break;
    //
    // default:
    //   Serial.print("What the fuck?\n");
    //   break;
    // }
  }
}
