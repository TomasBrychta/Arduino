#include <SdFat.h>
#include <Keypad.h>

const int chipSelect = 53;  // Pin connected to the CS pin of the SD card module

const byte ROW_NUM = 4; // Four rows
const byte COLUMN_NUM = 4; // Four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {49, 48, 47, 46}; // Connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {45, 44, 43, 42}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

SdFat SD;

const char* scriptExtensions[] = {"txt", "ps1", "bat", "cmd", "sh", "vbs", "py", "cpp", "java", "html", "css", "js", "php", "json", "xml", "ini"};

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // wait for serial port to connect.
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization done.");

  pinMode(53, OUTPUT); // Set the pin for the SD card module CS as output

  // Act like a keyboard upon connection
  delay(1000); // wait for the system to recognize the Arduino
  Serial.println("Arduino is now acting like a keyboard.");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println("Key Pressed: " + String(key));

    // Check if the pressed key corresponds to a script file
    if (key >= '1' && key <= '9') {
      int scriptNumber = key - '1';
      executeScript(scriptNumber);
    } else if (key == 'A') {
      executeScript(9); // Script A
    } else if (key == 'B') {
      executeScript(10); // Script B
    } else if (key == 'C') {
      executeScript(11); // Script C
    } else if (key == 'D') {
      executeScript(12); // Script D
    } else if (key == '*') {
      executeScript(13); // Script *
    } else if (key == '0') {
      executeScript(14); // Script 0
    } else if (key == '#') {
      executeScript(15); // Script #
    }
  }
}

void executeScript(int scriptNumber) {
  // Check if the scriptNumber is within bounds
  if (scriptNumber >= 0 && scriptNumber < sizeof(scriptExtensions) / sizeof(scriptExtensions[0])) {
    String fileName = "script" + String(scriptNumber + 1) + "_" + scriptExtensions[scriptNumber];
    File scriptFile = SD.open(fileName.c_str());

    if (scriptFile) {
      while (scriptFile.available()) {
        char character = scriptFile.read();
        Serial.write(character);

        // Simulate keyboard input
        //BYLO-ODKOMENTOVANO-Keypad.write(character);

        // Add a delay between key presses if needed
        delay(50);
      }

      scriptFile.close();
      Serial.println("Script executed.");
    } else {
      Serial.println("Error opening script file: " + fileName);
    }
  } else {
    Serial.println("Invalid script number: " + String(scriptNumber));
  }
}
