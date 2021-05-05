/**********************************************************
 * Projekt 7 - MULTIPLE Lysdioder
 * 
 * Låt åtta lysdioder dansa! 
/**********************************************************/

int ledPins[] = {2,3,4,5,6,7,8,9};

void setup()
{
 // initierar alla 8 stift som UTSIGNAL 
  pinMode(ledPins[0],OUTPUT);  // ledPins[0] = 2
  pinMode(ledPins[1],OUTPUT);  // ledPins[1] = 3
  pinMode(ledPins[2],OUTPUT);  // ledPins[2] = 4
  pinMode(ledPins[3],OUTPUT);  // ledPins[3] = 5
  pinMode(ledPins[4],OUTPUT);  // ledPins[4] = 6
  pinMode(ledPins[5],OUTPUT);  // ledPins[5] = 7
  pinMode(ledPins[6],OUTPUT);  // ledPins[6] = 8
  pinMode(ledPins[7],OUTPUT);  // ledPins[7] = 9
}

void loop()
{
  /*
  Det har inaktiverats några funktioner genom att kommentera 
  bort dem. För att prova olika beteende på Lysdioder, ta bort 
  kommentaren "//" framför funktionen du vill köra och lägg 
  till kommentaren "//" framför dem du inte vill köra. 
  Ja, inaktivera/kommentera bort dessa funktioner du vill inte köra. 
  */
  
  oneAfterAnother();  // Tänd alla lysdioderna i tur och ordning. 
  
  //oneOnAtATime();   // Slå på en LED i taget.
  
  //pingPong();      // Samma som oneOnAtATime() men ändra riktning 
                     // när LED når kanten.

  //marquee();       // Chase ljus(lights) som du ser på teaterskyltar 
  
  //randomLED();     // Lysdioder blinkar slumpmässigt
}

/******************************************************************
 * oneAfterAnother()
 *
 * Denna funktion tänder alla lysdioder, pausar och sedan släcker
 * alla lysdioderna. Funktionen använder sig av for() loopar och
 * arrayen för att göra detta med minimal kod. 
/*****************************************************************/
void oneAfterAnother()
{
  int index;
  int delayTime = 100; // millisekunder för att pausa mellan lysdioderna
                       // gör detta mindre för snabbare växling.
                       
  // Alla lysdioder sätts på:  
  for(index = 0; index <= 7; index = ++index) // går igenom index från 0 till 7
  {
    digitalWrite(ledPins[index], HIGH);
    delay(delayTime);    
  }                                  

  // Alla lysdioder stängs av: 
  for(index = 7; index >= 0; index = --index)  // går igenom index från 7 till 0
  {
    digitalWrite(ledPins[index], LOW);
    delay(delayTime);
  }               
}
 
/*****************************************************************
 * oneOnAtATime()
 * 
 * Denna funktion kommer att gå igenom lysdioderna och tända bara
 * en i taget. Funtionen slår varje lysdiod PÅ och sedan AV innan 
 * den går till nästa lysdiod. 
/****************************************************************/
void oneOnAtATime()
{
  int index;
  int delayTime = 100;
  
  for(index = 0; index <= 7; index = ++index)
  {
    digitalWrite(ledPins[index], HIGH); 
    delay(delayTime);                   
    digitalWrite(ledPins[index], LOW); 
  }
}

/*****************************************************************
 * pingPong()
 *
 * Denna funktion kommer att gå igenom lysdioderna och tända en i 
 * taget i båda riktningarna. Det finns ingen fördröjning mellan 
 * lysdioden som släckt och nästa påslagen lysdioden. Detta skapar 
 * ett jämnt mönster för lysdioderna.
/****************************************************************/
void pingPong()
{
  int index;
  int delayTime = 100; // milliseconds to pause between LEDs
   
  for(index = 0; index <= 7; index = ++index)   // step through the LEDs, from 0 to 7
  {
    digitalWrite(ledPins[index], HIGH);  // turn LED on
    delay(delayTime);                    // pause to slow down
    digitalWrite(ledPins[index], LOW);   // turn LED off
  }
 
  for(index = 7; index >= 0; index = --index)   // step through the LEDs, from 7 to 0
  {
    digitalWrite(ledPins[index], HIGH);  // turn LED on
    delay(delayTime);                    // pause to slow down
    digitalWrite(ledPins[index], LOW);   // turn LED off
  }
}

/*****************************************************************
 * marquee()
 * 
 * Denna funktion kommer att efterlikna "chase lights" som de 
 * som finns runt teaterskyltar (i USA).
/****************************************************************/
void marquee()
{
  int index;
  int delayTime = 200;
  
  // Gå igenom de fyra första lysdioderna 
  // (Vi tänder en i nedre 4 och en i övre 4)
  
  for(index = 0; index <= 3; index++) // går från 0 till 3
  {
    digitalWrite(ledPins[index], HIGH);    // slå på en lysdiod
    digitalWrite(ledPins[index+4], HIGH);  // Hoppa över fyra o slå på den lysdioden
    delay(delayTime);                      // Pausa för att sakta ner sekvensen
    digitalWrite(ledPins[index], LOW);     // Slå av lysdioden
    digitalWrite(ledPins[index+4], LOW);   // Hoppa över fyra och slå av den lysdioden
  }
}

/*****************************************************************
 * randomLED()
 * 
 * Denna funktion slår på slumpmässiga lysdioder. 
 * KAN DU ÄNDRA DET SÅ ATT MAN FÅR SLUMPMÄSSIGA TIDER???
/****************************************************************/
void randomLED()
{
  int index;
  int delayTime;
  
  index = random(8);  // välj ett slumpmässigt tal mellan 0 och 7
  delayTime = 100;
  
  digitalWrite(ledPins[index], HIGH);  // slå på
  delay(delayTime);                    // pausa för att sakta ner
  digitalWrite(ledPins[index], LOW);   // slå av
}
