/**********************************************
*  Projekt 15 - LCD-Display
*  visar en text på LCD.
***********************************************/

// Ladda ner LiquidCrystal-biblioteket
#include <LiquidCrystal.h>

// Initiera biblioteket med de stift vi använder.
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
  lcd.clear();      // Rensa gamla data som visas på displayen
}

void loop()
{
  lcd.setCursor(0, 0); // markören ställs in till kolumn 0, rad 0. 
  lcd.print("Hello EE19D!"); 
}
