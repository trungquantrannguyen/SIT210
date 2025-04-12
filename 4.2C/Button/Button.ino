#include <Wire.h>
#include <BH1750.h>
#include <Arduino.h>

const int buttonPin = 2;  // Push button input
const int ledButton = 3;  // LED toggled by button
const int ledLight = 4;   // LED controlled by light sensor

volatile int buttonState;
bool ledLightState = false;

unsigned long lastLightCheck = 0;
const unsigned long lightInterval = 500;

BH1750 lightMeter;

// === Interrupt: Button Press ===
void handleButtonPress() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledButton, !digitalRead(ledButton));
  Serial.print("Button pressed, LED toggled ");
  Serial.println(digitalRead(ledButton));
}


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledButton, OUTPUT);
  pinMode(ledLight, OUTPUT);

  Serial.begin(9600);
  while (!Serial)
    ;  // Wait for Serial Monitor

  Wire.begin();
  if (!lightMeter.begin()) {
    Serial.println("BH1750 not found!");
    while (1)
      ;
  }

  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, FALLING);

}

void loop() {
  // === Push Button Interrupt Handler ===
  // if (buttonToggled) {
  //   buttonToggled = false;
  //   digitalWrite(ledButton, !digitalRead(ledButton));
  //   Serial.println("Button pressed, LED toggled.");
  // }

  // === Light Sensor Triggered from Timer Flag ===
  if (millis() - lastLightCheck >= lightInterval) {
    lastLightCheck = millis();

    float lux = lightMeter.readLightLevel();
    Serial.print("Light level: ");
    Serial.println(lux);

    if (lux < 20.0) {
      ledLightState = true;
    } else {
      ledLightState = false;
    }
    digitalWrite(ledLight, ledLightState);
  }
}
