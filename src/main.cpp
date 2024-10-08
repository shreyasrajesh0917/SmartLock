#include <Arduino.h>
#include <Keypad.h>
#include <string>

using namespace std;

char matrix[4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
byte rowPins[4] = {26, 25, 33, 32};
byte colPins[4] = {13, 12, 14, 27};

Keypad keypad = Keypad(makeKeymap(matrix), rowPins, colPins, 4, 4);

string passkey = "1234";
string current = "";

void setup() 
{
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() 
{
  char key = keypad.getKey();
  if (key)
  {
    Serial.println(key);
  }
}
