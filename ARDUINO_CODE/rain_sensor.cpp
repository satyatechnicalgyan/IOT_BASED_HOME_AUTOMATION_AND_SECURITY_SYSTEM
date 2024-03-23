const int rainSensorPin = A0; // Analog pin connected to the rain sensor
const int ledPin = 13; // Pin connected to the LED for indication

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(rainSensorPin); // Read the analog value from the rain sensor
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);

  if (sensorValue < 500) { // Adjust the threshold based on your sensor's reading
    Serial.println("Rain detected!");
    digitalWrite(ledPin, HIGH); // Turn on LED to indicate rain
    
  } else {
    Serial.println("No rain detected.");
    digitalWrite(ledPin, LOW); // Turn off LED
  }

  delay(1000); // Delay before next reading
}
