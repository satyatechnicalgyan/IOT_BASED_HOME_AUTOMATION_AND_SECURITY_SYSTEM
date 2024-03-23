Here's a comprehensive code for Arduino Nano that integrates the functionalities of DHT11 temperature and humidity sensor, rain sensor, PIR motion sensor, MQ-6 gas sensor, buzzer, fan, light, TV, AC, door lock with keypad matrix, and a 16x4 LCD display, along with an emergency panic button:

```cpp
#include <DHT.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2            // Pin connected to the DHT11 sensor
#define DHTTYPE DHT11       // DHT 11

#define RAIN_SENSOR_PIN A0  // Analog pin connected to the rain sensor
#define PIR_PIN 3           // Pin connected to the PIR motion sensor
#define MQ_PIN A1           // Analog pin connected to the MQ-6 sensor

#define LIGHT_PIN 4         // Pin connected to the light relay module
#define TV_PIN 5            // Pin connected to the TV relay module
#define AC_PIN 6            // Pin connected to the AC relay module
#define FAN_PIN 7           // Pin connected to the fan relay module
#define DOOR_LOCK_PIN 8     // Pin connected to the door lock relay module
#define BUZZER_PIN 9        // Pin connected to the buzzer

#define PANIC_BUTTON_PIN 10 // Pin connected to the emergency panic button

const byte ROWS = 4;        //four rows
const byte COLS = 3;        //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {A2, A3, A4, A5};  //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 12, 13};      //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal_I2C lcd(0x27, 16, 4);  // Address 0x27, 16 columns, 4 rows

DHT dht(DHTPIN, DHTTYPE);

bool panicButtonPressed = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(RAIN_SENSOR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(MQ_PIN, INPUT);
  
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(TV_PIN, OUTPUT);
  pinMode(AC_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(DOOR_LOCK_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  pinMode(PANIC_BUTTON_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Welcome to Smart");
  lcd.setCursor(0, 1);
  lcd.print("Home System");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read sensors
  float humidity = dht.readHumidity();    // Read humidity (in %)
  float temperature = dht.readTemperature(); // Read temperature (in Celsius)
  int rainSensorValue = analogRead(RAIN_SENSOR_PIN);
  int pirSensorValue = digitalRead(PIR_PIN);
  int mqSensorValue = analogRead(MQ_PIN);

  // Check emergency panic button
  if (digitalRead(PANIC_BUTTON_PIN) == LOW) {
    if (!panicButtonPressed) {
      panicButtonPressed = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Emergency Panic");
      lcd.setCursor(0, 1);
      lcd.print("Button Pressed!");
      digitalWrite(BUZZER_PIN, HIGH);
      delay(2000);
    }
  } else {
    panicButtonPressed = false;
    digitalWrite(BUZZER_PIN, LOW);
    lcd.clear();
  }

  // Display sensor readings on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  lcd.setCursor(0, 2);
  lcd.print("Rain: ");
  lcd.print(rainSensorValue);
  lcd.print("  ");

  lcd.setCursor(0, 3);
  lcd.print("PIR: ");
  lcd.print(pirSensorValue);
  lcd.print("  ");

  lcd.setCursor(10, 2);
  lcd.print("Gas: ");
  lcd.print(mqSensorValue);
  lcd.print("  ");

  // Check rain sensor
  if (rainSensorValue < 500) { // Adjust the threshold based on your sensor's reading
    lcd.setCursor(6, 2);
    lcd.print("Rain: Detected");
  } else {
    lcd.setCursor(6, 2);
    lcd.print("Rain: None    ");
  }

  // Check PIR sensor
  if (pirSensorValue == HIGH) {
    lcd.setCursor(5, 3);
    lcd.print("Motion: Detected");
  } else {
    lcd.setCursor(5, 3);
    lcd.print("Motion
