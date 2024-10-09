#include <Arduino.h>
#include <Keypad.h>
#include <string>

using namespace std;

char matrix[4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
byte rowPins[4] = {26, 25, 33, 32};
byte colPins[4] = {13, 12, 14, 27};

Keypad keypad = Keypad(makeKeymap(matrix), rowPins, colPins, 4, 4);

string passkey = "AB12";
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
    if (current.size() > passkey.size())
    {
      Serial.println("Passkey too long");
      // Make LED turn red
      delay(2000);
      current = "";
    }

    if (key != '*' && current.size() < passkey.size())
    {
      Serial.println(key); // optional for testing
      current += key;
    }
    else if (key == '*' && !current.empty())
    {
      if (current == passkey)
      {
        Serial.println("Correct passkey");
        // Make LED turn green
        delay(2000);
        // Send signal to unlock
        current = "";
      }
      else
      {
        Serial.println("Wrong passkey");
        // Make LED turn red
        delay(2000);
        current = "";
      }
    }
  }
}
