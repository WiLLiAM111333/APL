/*********************************************************
*  Projekt 15 - LCD-Display - ovn 2
*  Den scrollar text åt höger och vänster.
**********************************************************/

// Ladda ner LiquidCrystal-biblioteket
#include <LiquidCrystal.h>

// Initiera biblioteket med de stift du använder.
const int rs = 2;
const int en = 4;
const int d4 = 8;
const int d5 = 9;
const int d6 = 10;
const int d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  lcd.begin(16, 2); // Initiera 16x2 LCD 
  lcd.clear();      // Rensa gamla data som visas på displayen.
  lcd.print("Hello, EE19D!");
  delay(1000);
}

void loop() 
{ 
  // scrollar 13 platser (textens längd) åt vänster.
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scrollar en position/plats till vänster
    lcd.scrollDisplayLeft();
    // väntar lite:
    delay(150);
  }

  // scrollar 29 positioner (textens längd + displayens längd) åt höger.
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // scrollar en position till höger
    lcd.scrollDisplayRight();
    delay(150);
  }

  // scrollar 16 positioner (displayens längd + textens längd) åt vänster.
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }
}
