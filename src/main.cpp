#include <Arduino.h>
#include <Keypad.h>

char keyMap[4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
byte rowPins[4] = {26, 25, 33, 32};
byte colPins[4] = {13, 12, 14, 27};

Keypad keypad = Keypad(makeKeymap(keyMap), rowPins, colPins, 4, 4);

char passkey[] = "AB12\0";
char current[5] = ""; // 4 characters + null terminator
int currentIndex = 0; // Renamed from 'index' to 'currentIndex'

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  char key = keypad.getKey();

  if (key)
  {
    // Serial.println(key); // For testing keypress

    if (key != '*')
    {
      if (currentIndex < sizeof(passkey) - 2)
      {
        current[currentIndex] = key;
        currentIndex++;
        Serial.println(current);
      }
      else
      {
        Serial.println("Passkey too long");
        memset(current, '\0', sizeof(current)); // Reset the entire array
        currentIndex = 0;
      }
    }
    else
    {
      current[currentIndex] = '\0'; // Null-terminate the string
      if (strcmp(current, passkey) == 0)
      {
        Serial.println("Correct passkey");
        // Trigger your unlock logic here
      }
      else
      {
        Serial.println("Wrong passkey");
      }
      currentIndex = 0;                       // Reset for next attempt
      memset(current, '\0', sizeof(current)); // Reset the entire array
    }
  }
}
