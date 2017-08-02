#include <SPI.h>
#include <TM1650.h>
#include <Wire.h>

TM1650 Disp4Seg;
char endMarker = '\n';
int status = 0;
bool building = false;
bool jourfix = false;
int price = 0;
unsigned long time = 0;
String output = "";

#define RED 2
#define YELLOW 3
#define GREEN 4
#define RED_BUILD 5
#define YELLOW_BUILD 6
#define GREEN_BUILD 7

#define SW1 8
#define SW2 9
#define SW3 10
#define SW4 11
#define SW5 12
#define SW6 13

void displayPrice(int price) {
  Disp4Seg.DisplayON();
  Disp4Seg.SetBrightness(1);
  Disp4Seg.SetDot(1, true);
  Disp4Seg.WriteNum(price);
}

void resetRelais() {
  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED_BUILD, HIGH);
  digitalWrite(YELLOW_BUILD, HIGH);
  digitalWrite(GREEN_BUILD, HIGH);
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000);
  Disp4Seg.Init();
  delay(1000);

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED_BUILD, OUTPUT);
  pinMode(YELLOW_BUILD, OUTPUT);
  pinMode(GREEN_BUILD, OUTPUT);

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);
  pinMode(SW5, INPUT);
  pinMode(SW6, INPUT);

  resetRelais();

  Serial.println("Arduino ready");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil(endMarker);
    input.trim();

    if (input.length() == 6) {
      time = millis();

      status = input.substring(0, 1).toInt();
      price = input.substring(3).toInt();

      building = input.substring(1, 2).toInt() == 1;
      jourfix = input.substring(3, 4).toInt() == 1;

      resetRelais();

      if (building) {
        switch (status) {
        case 1:
          digitalWrite(RED_BUILD, LOW);
          break;

        case 2:
          digitalWrite(YELLOW_BUILD, LOW);
          break;

        case 3:
          digitalWrite(GREEN_BUILD, LOW);
          break;
        }
      } else {
        switch (status) {
        case 1:
          digitalWrite(RED, LOW);
          break;

        case 2:
          digitalWrite(YELLOW, LOW);
          break;

        case 3:
          digitalWrite(GREEN, LOW);
          break;
        }
      }

      if (price != 0) {
        displayPrice(price);
      }

      output = digitalRead(SW6);
      output += digitalRead(SW5);
      output += digitalRead(SW4);
      output += digitalRead(SW3);
      output += digitalRead(SW2);
      output += digitalRead(SW1);

      Serial.println(output);

    } else {
      Serial.println("wtf");
    }
  }

  if (millis() - time >= 5000) {
    Disp4Seg.DisplayOFF();
  }
}
