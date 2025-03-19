#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;  // Create BH1750 object

void setup() {
    Serial.begin(115200);
    Wire.begin();  // Start I2C
    lightMeter.begin();  // Initialize BH1750 sensor
    Serial.println("BH1750 Light Sensor Initialized");
}

void loop() {
    float lux = lightMeter.readLightLevel();  // Read lux value
    Serial.print("Light Level: ");
    Serial.print(lux);
    Serial.println(" lx");  // Print lux value

    delay(1000);  // Wait 1 second before next reading
}
