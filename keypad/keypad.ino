 
// Include the Keypad library
#include <Keypad.h>

#define c1 6 
#define c2 7
#define c3 8
#define r1 9
#define r2 10
#define r3 11 
#define r4 12
 
// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 3;
 
// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6',},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
 
// Connections to Arduino
byte rowPins[ROWS] = {r4, r3,  r2, r1,};
byte colPins[COLS] = { c2,c3,  c1 , };
 
// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 
void setup() {
  // Setup serial monitor
  Serial.begin(9600);
}
 
void loop() {
  // Get key value if pressed
  char customKey = customKeypad.getKey();
 
  if (customKey) {
    // Print key value to serial monitor
    Serial.println(customKey);
  }
}
