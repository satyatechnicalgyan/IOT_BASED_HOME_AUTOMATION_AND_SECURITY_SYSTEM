#define LIGHT_PIN 4     // Pin connected to the light relay module
#define BULB_PIN 5      // Pin connected to the bulb relay module
#define AC_PIN 6        // Pin connected to the AC relay module
#define TV_PIN 7        // Pin connected to the TV relay module
#define FAN_PIN 8       // Pin connected to the fan relay module

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(BULB_PIN, OUTPUT);
  pinMode(AC_PIN, OUTPUT);
  pinMode(TV_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  // Initially turn off all devices
  digitalWrite(LIGHT_PIN, LOW);
  digitalWrite(BULB_PIN, LOW);
  digitalWrite(AC_PIN, LOW);
  digitalWrite(TV_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);

  Serial.begin(9600);
}

void loop() {
  // Sample code to control devices based on input (you can modify this logic)

  // If '1' is received from serial monitor, turn on light
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '1') {
      digitalWrite(LIGHT_PIN, HIGH);
      Serial.println("Light turned on.");
    }
    else if (command == '2') {
      digitalWrite(BULB_PIN, HIGH);
      Serial.println("Bulb turned on.");
    }
    else if (command == '3') {
      digitalWrite(AC_PIN, HIGH);
      Serial.println("AC turned on.");
    }
    else if (command == '4') {
      digitalWrite(TV_PIN, HIGH);
      Serial.println("TV turned on.");
    }
    else if (command == '5') {
      digitalWrite(FAN_PIN, HIGH);
      Serial.println("Fan turned on.");
    }
    else if (command == '0') {
      // Turn off all devices
      digitalWrite(LIGHT_PIN, LOW);
      digitalWrite(BULB_PIN, LOW);
      digitalWrite(AC_PIN, LOW);
      digitalWrite(TV_PIN, LOW);
      digitalWrite(FAN_PIN, LOW);
      Serial.println("All devices turned off.");
    }
  }
}
