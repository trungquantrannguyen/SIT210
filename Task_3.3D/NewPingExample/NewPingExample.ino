// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>
#include "secrets.h"

#define TRIGGER_PIN 12    // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 11       // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// WiFi settings
const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;

// Clients
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// MQTT broker settings
const char broker[] = "broker.emqx.io";  // Public test broker
int port = 1883;
const char topic[] = "SIT210/wave";

const char clientId[] = "mqttx_ed9312e7";

unsigned long lastWaveTime = 0;
const int waveCooldown = 3000;  // ms between waves to prevent spamming


const int ledPin = 4;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600);  // Open serial monitor at 9600 baud to see ping results.
  pinMode(ledPin, OUTPUT);
  while (!Serial)
    ;

  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(WiFi.status());
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" connected!");

  // Connect to MQTT
  mqttClient.setId(clientId);
  Serial.print("Connecting to MQTT broker...");
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error: ");
    Serial.println(mqttClient.connectError());
    while (1)
      ;
  }
  Serial.println(" connected!");

  // Subscribe to the topic
  mqttClient.subscribe(topic);
  Serial.print("Subscribed to topic: ");
  Serial.println(topic);
}

void loop() {
  // Check for incoming messages
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    Serial.print("Received on ");
    Serial.print(mqttClient.messageTopic());
    Serial.print(": ");

    while (mqttClient.available()) {
      char c = mqttClient.read();
      Serial.print(c);
    }
    Serial.println();
    if(messageSize == 44){
      blink(2000);
    }
    if(messageSize == 43){
    blink(100);
    blink(100);
    blink(100);
    }
  }

  // Publish every 3 seconds
  int distance = sonar.ping_cm();
  if (distance > 0 && millis() - lastWaveTime > waveCooldown) {
    // Serial.print("Ping ");
    // Serial.print(distance);
    // Serial.println("cm");
    if (distance < 50 && distance > 10) {
      wavePublisher();
    }
    if (distance < 10) {
      patPublisher();
    }
  }
}

void blink(int time) {
  digitalWrite(ledPin, HIGH);
  delay(time);
  digitalWrite(ledPin, LOW);
  delay(time);
}

void wavePublisher() {
  String message = "Waved from Tran Nguyen Trung Quan 225054634";
  mqttClient.beginMessage(topic);
  mqttClient.print(message);
  mqttClient.endMessage();

  lastWaveTime = millis();
}

void patPublisher() {
  String message = "Patted from Tran Nguyen Trung Quan 225054634";
  mqttClient.beginMessage(topic);
  mqttClient.print(message);
  mqttClient.endMessage();

  lastWaveTime = millis();
}