/****************************************************
* Projekt 3 - Tryckknappbrytaren övn 1
* Två tryckknappsbytare, den ena tryckknappen tänder 
* lysdioden och den andra släcker lysdioden
*****************************************************/

const int buttonPinON  = 2;
const int buttonPinOFF = 3;   
const int ledPin = 13;

//int lastButtonStateOFF, lastButtonStateON;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPinOFF, INPUT);
  pinMode(buttonPinON, INPUT);
}

void loop() 
{
  int buttonStateOFF = digitalRead(buttonPinOFF);
  int buttonStateON  = digitalRead(buttonPinON);

  
  if (buttonStateON == HIGH && buttonStateOFF == LOW) //lastButtonStateON==LOW && 
  {
    digitalWrite(ledPin, HIGH);
  }

  // lastButtonStateOFF == LOW &&
  if (buttonStateOFF == HIGH && buttonStateON == LOW) //lastButtonStateOFF==LOW && 
  {
    digitalWrite(ledPin, LOW);
  } 
  
  //lastButtonStateOFF = buttonStateOFF;
  //lastButtonStateON  = buttonStateON;
  //delay(10);
}
