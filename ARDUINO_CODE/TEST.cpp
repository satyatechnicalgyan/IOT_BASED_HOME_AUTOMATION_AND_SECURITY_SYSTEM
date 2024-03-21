#include <DHT.h>

#define DHTPIN 2        // Pin connected to the DHT11 sensor
#define DHTTYPE DHT11   // DHT 11

#define PIRPIN 3        // Pin connected to the PIR motion sensor
#define MQPIN A0        // Pin connected to the MQ-6 sensor

#define SMOKE_THRESHOLD 100  // Adjust this threshold as needed for your setup

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 Humidity & Temperature Sensor with PIR Motion Sensor and MQ-6 Smoke Sensor\n");

  pinMode(PIRPIN, INPUT);
  pinMode(MQPIN, INPUT);
  
  dht.begin();
}

void loop() {
  // Read motion sensor state
  int motionState = digitalRead(PIRPIN);

  // Read temperature and humidity data
  float humidity = dht.readHumidity();        // Read humidity (in %)
  float temperature = dht.readTemperature();  // Read temperature (in Celsius)

  // Read smoke sensor value
  int smokeValue = analogRead(MQPIN);

  // Check if any sensor reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Display temperature, humidity, and motion state on the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  if (motionState == HIGH) {
    Serial.println("Motion Detected!");
  } else {
    Serial.println("No Motion Detected.");
  }

  // Check smoke level
  Serial.print("Smoke Level: ");
  Serial.println(smokeValue);

  if (smokeValue > SMOKE_THRESHOLD) {
    Serial.println("Smoke Detected!");
  } else {
    Serial.println("No Smoke Detected.");
  }

  delay(2000);  // Wait a few seconds before next reading
}

