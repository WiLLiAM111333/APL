#include <LiquidCrystal.h>

const int rs = 2;
const int en = 4;
const int d4 = 8;
const int d5 = 9;
const int d6 = 10;
const int d7 = 11;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char message[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'E', 'E', '1', '9', 'D' };

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  
  for(int i = 0; i < 11; i++) {
    lcd.print(message[i]);
    delay(500);  
  }

  lcd.setCursor(16, 1);
  lcd.autoscroll();

  for(int i = 0; i < 11; i++) {
    lcd.print(message[i]);
    delay(500);
  }

  lcd.noAutoscroll();

  lcd.clear();
}
