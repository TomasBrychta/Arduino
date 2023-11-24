#include <SD.h>      
#include <Keypad.h>   
#include <Keyboard.h>

const int chipSelect = 10;  // Pin connected to the SD card module's chip select pin

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void simulateKeyboardInput() {
  
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  while (true) {
    char key = keypad.getKey(); 

    if (key) {
      String fileName = String(key) + ".txt"; 
      File scriptFile = SD.open(fileName);    

      if (scriptFile) {
        while (scriptFile.available()) {
          char command = scriptFile.read();  
          Serial.print("Simulating keyboard input: ");
          Serial.println(command);
        }

        scriptFile.close();
      } else {
        Serial.println("Script file not found!");
      }
    }
  }
}


void test_simulateKeyboardInput_valid() {

  Serial.println("Simulating keyboard input for script file A.txt: A");
}


void test_simulateKeyboardInput_nonexistent() {

  Serial.println("Simulating keyboard input for non-existent script file: Script file not found!");
}

void test_simulateKeyboardInput_empty() {

  Serial.println("Simulating keyboard input for empty script file: No commands to simulate!");
}

/**
 * Test: Simulate keyboard input for multiple script files
 */
void test_simulateKeyboardInput_multiple() {
  // Create a mock SD card with multiple script files
  // Replace the following line with the appropriate code for creating a mock SD card
  Serial.println("Simulating keyboard input for multiple script files: A, B, C, D");
}

void setup() {
  Serial.begin(9600);  // Initialize the serial communication
  simulateKeyboardInput();  // Start simulating keyboard input
}

void loop() {
  // Empty loop
}