#include "arduino_secrets.h"
#include <WiFiNINA.h>
#include <Wire.h>
#include <BH1750.h>

char ssid[] = SECRET_SSID;  // your network SSID (name)
char pass[] = SECRET_PASS;  // your network password (use for WPA, or use as key for WEP)e
char webhookKeys[] = SECRET_WEBHOOK_KEY;

char HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME = "/trigger/Recieved_data/with/key/dQzUXSs18kx7QFgD6YkZaz";  // change your EVENT-NAME and YOUR-KEY

WiFiClient client;
BH1750 lightMeter;

void setup() {
  WiFi.begin(ssid, pass);
  Serial.begin(9600);

  while (!Serial)
    ;
  Serial.println(HOST_NAME);

  // connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // if connected:
    Serial.println("Connected to server");
  } else {  // if not connected:
    Serial.println("connection failed");
  }

  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use
  // Wire.begin(D2, D1);

  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));
}

void loop() {

  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
  if (lux > 10000) {
    // make a HTTP request:
    // send HTTP header
    String getHeader = "GET " + PATH_NAME + "?value1=Your%20terarium%20is%20not%20recieving%20direct%20sunlight%20at%20" + lux + "%20lx'" + " HTTP/1.1";
    client.println(getHeader);
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println();  // end HTTP header
    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }
  } else {
    // make a HTTP request:
    // send HTTP header
    String getHeader = "GET " + PATH_NAME + "?value1=Your%20terarium%20is%20not%20recieving%20direct%20sunlight%20at%20" + lux + "%20lx" + " HTTP/1.1";
    client.println(getHeader);
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println();  // end HTTP header
    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }
  }

  //delay 2 hours
  delay(1000 * 3600 * 2);
}
