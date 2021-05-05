/******************************************************************
*  Projekt 15 - LCD-Display - ovn1
*  Den skriver ut ett tecken i taget och scrollar det åt vänster.
*******************************************************************/
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

char message[] = {'H','e','l','l','o',' ','E','E','1','9','D','!'};

void setup()
{
  lcd.begin(16, 2); // Initiera 16x2 LCD 
  lcd.clear();      // Rensa gamla data som visas på displayen.
}

void loop() 
{ 
  lcd.setCursor(0, 0);
  
  // Skriver ut ett tecken i taget
  for (int index = 0; index < 12; index++) 
  {
    lcd.print(message[index]);
    delay(500);
  }

  lcd.setCursor(16, 1);

  // ställer in displayen så att den scrollar automatiskt:
  lcd.autoscroll();

  // Skriver ut ett tecken i taget
  for (int index = 0; index < 12; index++) 
  {
    lcd.print(message[index]);
    delay(500);
  }

  // täng av automatisk scrollning
  lcd.noAutoscroll();

  // rensa displayen för nästa loop:
  lcd.clear();
}
