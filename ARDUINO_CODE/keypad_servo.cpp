#include <Keypad.h>
#include <Servo.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

// Define the keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {12, 11, 10, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6};    //connect to the column pinouts of the keypad

// Create the Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define the correct code
const char* correctCode = "1234"; // Change this to your desired code

Servo doorLockServo; // Create a servo object
int lockPosition = 0; // Lock position angle
int unlockPosition = 145; // Unlock position angle

void setup() {
  Serial.begin(9600);
  doorLockServo.attach(2); // Attach the servo to pin 2
  lockDoor(); // Lock the door initially
}

void loop() {
  char key = keypad.getKey(); // Read the key pressed

  if (key) {
    Serial.println(key);
    if (key == '#') { // Check if the entered code is complete
      checkCode();
    }
  }
}

void checkCode() {
  char enteredCode[5]; // Assuming a maximum of 4 digit code
  int index = 0;

  // Prompt user to enter the code
  Serial.println("Enter the code followed by #:");

  while (true) {
    char key = keypad.getKey();
    if (key) {
      Serial.print(key);
      enteredCode[index++] = key;
    }

    if (index == 4 || key == '#') { // Check if the entered code is complete
      enteredCode[index] = '\0'; // Null terminate the string
      Serial.println();

      // Check if entered code matches the correct code
      if (strcmp(enteredCode, correctCode) == 0) {
        Serial.println("Access Granted!");
        unlockDoor(); // Unlock the door
      } else {
        Serial.println("Access Denied!");
      }
      break;
    }
  }
}

void unlockDoor() {
  doorLockServo.write(unlockPosition); // Unlock the door
  Serial.println("Door Unlocked!");
  delay(5000);
  lockDoor();
  
}

void lockDoor() {
  doorLockServo.write(lockPosition); // Lock the door
  Serial.println("Door Locked!");
}
