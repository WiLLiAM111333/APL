#include <LiquidCrystal.h>

const int rs = 2;
const int en = 4;
const int d4 = 8;
const int d5 = 9;
const int d6 = 10;
const int d7 = 11;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {  
  int cursorPos[2] = { 0, 0 };
  
  for(int i = 65; i <= 90; i++) {
    lcd.setCursor(cursorPos[0], cursorPos[1]);
    lcd.print(char(i));

    if(cursorPos[1] < 1) {
      if(cursorPos[0] < 16) {
        cursorPos[0]++; 
      } else {
        cursorPos[1]++;
      } 
    } else {
      cursorPos[0]--;
    }
    
    delay(150);
  }
  
  lcd.clear();
  delay(1000);
}