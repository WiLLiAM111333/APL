/******************************************* 
*  Projekt 3 - Tryckknappbrytare övn 3
********************************************/

int pressLength_milliSeconds = 0;

int pushRed_milliSeconds    = 100;
int pushYellow_milliSeconds = 2000;
int turnOff_milliSeconds    = 3000;

const int buttonPin =  2;

const int ledPinRed    = 12;
const int ledPinYellow = 13;   

void setup() {
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  while( digitalRead(buttonPin) == HIGH )
  {
    delay(100);
    pressLength_milliSeconds = pressLength_milliSeconds + 100;
    
    Serial.print("milliseconds = ");
    Serial.println(pressLength_milliSeconds);
  }
  
  if( pressLength_milliSeconds >= turnOff_milliSeconds )
  {
    digitalWrite(ledPinRed, LOW);
    digitalWrite(ledPinYellow, LOW);
  }  
  else if( pressLength_milliSeconds >= pushYellow_milliSeconds )
  {
    digitalWrite(ledPinYellow, HIGH);
  }
  else if( pressLength_milliSeconds >= pushRed_milliSeconds )
  {
    digitalWrite(ledPinRed, HIGH);
  }
  
  pressLength_milliSeconds = 0;  
}
