/**************************************************************************
 * Projekt 14 - DC-Motor
 * 
 * MOTORSPINNING
 * Detta projekt kräver att du kör motorn med en NPN-transistor. 
 * Arduino kan bara köra cirka 40 mA ström per stift och en motor 
 * kräver upp till 150 mA. Transistorn förstärker strömmen
 **************************************************************************/

// Anslut transistorns bas till stift 9.
const int MOTOR_PIN = 9;

void setup()
{
  pinMode(MOTOR_PIN, OUTPUT);  // ställer in stiftet som en OUTPUT
  Serial.begin(9600);          // initiera seriell kommunikation
}


void loop()
{
  int onTime  = 3000;  // millisekunder för att slå på motorn
  int offTime = 3000;  // millisekunder för att stänga av motorn

  analogWrite(MOTOR_PIN, 255); // slå på motorn (full hastighet)  
  delay(onTime);               // väntetid för onTime millisekunder 
  analogWrite(MOTOR_PIN, 0);   // stäng av motorn
  delay(offTime);              // väntetid för offTime milliseconds
  

  // FÖR ATT TESTA DE BORTKOMMENTERADE FUNKTIONER NEDAN, TA BORT KOMMENTAR-TECKEN.
  
  //speedUpAndDown(); 
  //serialSpeed();
}


/***********************************************************************
 * Denna funktion accelererar upp motorn från 0 till full hastighet, 
 * för att sedan accelererar ned till 0.
 ***********************************************************************/
void speedUpAndDown()
{
  int speed;
  int delayTime = 1; // millisekunder mellan varje hastighetssteg

  // accelererar motorn
  for(speed = 0; speed <= 255; speed++)
  {
    analogWrite(MOTOR_PIN,speed); // ställer in denSerial.print("speed: ");
    delay(delayTime);             // väntetid mellan hastighetssteg 
    
    Serial.print("speed: ");
    Serial.println(speed);
  }
  // 
  for(speed = 255; speed >= 0; speed--)
  {
    analogWrite(MOTOR_PIN,speed); // ställer in den nya hastigheten 
    delay(delayTime);             // väntetid mellan hastighetssteg
    
    Serial.print("speed: ");
    Serial.println(speed);
  }
}

/*****************************************************************************
 * Funktionen uppmanar användaren att ange en hastighet på 0-255 genom den 
 * seriella monitorn så att motorn sedan roterar genom det angivna värdet. 
 *****************************************************************************/
void serialSpeed()
{
  int speed;

  // Detta meddelande nedan skrivs ut bara en gång på monitorn.
  Serial.println("Skriv en hastighet (0-255) i rutan ovan,");
  Serial.println("klicka sedan pa [skicka/send] eller tryck pa [retur]");
  Serial.println();  //Skriv ut en tom rad 

  // "true" är alltid sant, så detta kommer att slinga för alltid. 
  while(true)  
  {
    // Kontrollerar om inkommande data är tillgänglig: 
    while (Serial.available() > 0)
    {
      // parseInt() läser in det första heltalsvärdet från Serial Monitor.
      speed = Serial.parseInt();
      
      // begränsar hastigheten mellan 0 och 255 eftersom analogWrite() bara fungerar i detta intervall. 
      speed = constrain(speed, 0, 255); 
    
      //skriver ut den hastighet som du angav på monitorn. 
      Serial.print("Du staeller in hastighet till:  ");  
      Serial.println(speed);

      analogWrite(MOTOR_PIN, speed);  // ställer in motorns hastighet. 
    }
  }
}
