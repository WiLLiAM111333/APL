/*********************************************************************************
*  Projekt 15 - LCD-Display övn 11
*  Visning av klockan, inställning av klockans timmar, minuter och väckarklockan,
*  visning av rumstemperaturen och RGB-lysdioden som tänds med färg röd
*  när alarmen går, med färg gul när temperaturen är högre än 29 och lägre
*  45, eller/annars tänds med färgen grön.
**********************************************************************************/
#include <LiquidCrystal.h>

// DAGENS DATUM STÄLLS IN HÄR 
// Här hårdkodar vi datumet och dagen: Mon, Tue, Wed, Thu, Fri, Sat, Sun
String currentDay  = "Mon"; 
String currentDate = "26-04-2021";

// KLOCKANS TID STÄLLS IN HÄR 
// Här hårdkodar vi tiden
int hours   = 11;
int minutes = 29;
int seconds = 0;

// Initiera biblioteket med de stift vi använder.
const int RS = 2;
const int E  = 3;
const int D4 = 4;
const int D5 = 5;
const int D6 = 6;
const int D7 = 7;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

const int BUTTON_HOURS_PIN  = 8;
const int BUTTON_MINUTE_PIN = 9;
const int BUTTON_ALARM_PIN  = 10;
const int BUTTON_TEMP_DATE_PIN  = 11;
const int TEMPERATURE_PIN   = A2;
const int RED_PIN   = A3;
const int GREEN_PIN = A5;
const int BLUE_PIN  = A4;

// Alarms variabler 
int alarmHours   = 0;
int alarmMinutes = 0;
int alarmSeconds = 0;
bool alarmIsGoing = false;
bool alarmON      = false;

float degreesCelsius; // för lagring o visning av temperaturen.

int delayTime = 210; // fördröjningstid av inställning för timmar o minuter.
int oneSecond = 1000;

  
void setup()
{
  lcd.begin(16, 2);
  pinMode(BUTTON_HOURS_PIN,  INPUT_PULLUP);
  pinMode(BUTTON_MINUTE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_ALARM_PIN,  INPUT_PULLUP);
  pinMode(BUTTON_TEMP_DATE_PIN, INPUT_PULLUP);
  
  pinMode(RED_PIN,   OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN,  OUTPUT);
  
  Serial.begin(9600);
  
  lcd.clear();
}

void loop()
{
  if(alarmON == false){
    displayTimeLCD(hours, minutes, seconds, 0, 0, "TIME: ", ' ');
  }
  else{
    displayTimeLCD(hours, minutes, seconds, 0, 0, "TIME: ", 'A');
  }
   
  clockCounter();  
  
  timeSetting("clockTime");
  
  alarmSetting();
  
  activateRGB(); 
  
  displayTempOrDate();
}

/*******************************************
* Funktionen visar tiden på LCD-displayen
*******************************************/
void displayTimeLCD( int h, int m, int s, int col, int row, String msg, char option )
{
  lcd.setCursor(col, row);
  lcd.print(msg );

  if(h < 10) lcd.print(0);
  lcd.print(h);
  lcd.print(":");

  if(m < 10) lcd.print(0);
  lcd.print(m);
  lcd.print(":");

  if(s < 10) lcd.print(0);
  lcd.print(s);
  
  lcd.print(" ");
  lcd.print(option);
}

/*****************************************************
* Funktionen visar text på LCD-displayen.
******************************************************/
void displayMessageLCD(int col, int row, String message){
  lcd.setCursor(col, row);
  lcd.print(message);
}

/**********************************
* Funktionen räknar klockans tid
***********************************/
void clockCounter(){
  seconds++;
  if(seconds > 59)
  {
    seconds = 0;
    minutes++;

    if(minutes > 59)
    {
      minutes = 0;
      hours++;

      if(hours > 23)
      {
        hours = 0;
      }
    }
  }
  delay(oneSecond);
  checkAlarm();
}

/*********************************************** 
* Funktionen ställer in tiden på klockan 
************************************************/
void timeSetting(String type)
{
  //visar TIMMARNA på LCD när TIM-KNAPPEN blir intryck. 
  if(digitalRead(BUTTON_HOURS_PIN) == 0){
      if(type == "clockTime") displayMessageLCD(0, 1, "HOURS SETTING");
      hourSetting(type);
      if(type == "clockTime") displayMessageLCD(0, 1, "             ");
  }

  //visar MINUTERNA på LCD när MINUT-KNAPPEN blir intryck. 
  if(digitalRead(BUTTON_MINUTE_PIN) == 0){
     if(type == "clockTime") displayMessageLCD(0, 1, "MINUTE SETTING");
     minuteSetting(type);
     if(type == "clockTime") displayMessageLCD(0, 1, "              ");
  }
}

/***************************************************************************************
* Funktionen ställer in TIMMARNA och visar en text på LCD när TIM-KNAPPEN blir intryck. 
****************************************************************************************/
void hourSetting( String type )
{      
    do{
      if(type == "clockTime")
      {
        hours++;
        delay(delayTime);
        displayTimeLCD(hours, minutes, seconds, 0, 0, "TIME: ", ' ');
        if (hours == 23) hours = 0;
      }
      else
      {
        if (alarmHours == 23) alarmHours = 0;
        alarmHours++;
        delay(delayTime);
        displayTimeLCD(alarmHours, alarmMinutes, alarmSeconds, 0, 0, "TIME: ", ' ');
      }      
      if(digitalRead(BUTTON_HOURS_PIN) == 1) break;
      
    }while(true);  
}

/*************************************************************************************** 
* Funktionen ställer in MINUTERNA o visar en text på LCD när MINUT-KNAPPEN blir intryck. 
****************************************************************************************/
void minuteSetting( String type )
{       
    do{
      if(type == "clockTime")
      {
        if (minutes == 59) minutes = 0;
        minutes++;
        delay(delayTime);
        displayTimeLCD(hours, minutes, seconds, 0, 0, "TIME: ", ' ');
      }
      else
      {
        alarmMinutes++;
        delay(delayTime);
        displayTimeLCD(alarmHours, alarmMinutes, alarmSeconds, 0, 0, "TIME: ", ' ');
        if (alarmMinutes == 59) alarmMinutes = 0;
      } 
      
      if(digitalRead(BUTTON_MINUTE_PIN) == 1) break;
      
    }while(true);  
}

/*********************************************** 
* Funktionen ställer in väckarklockan 
************************************************/
void alarmSetting()
{
  bool larmExecuting           = false;
  int pressLength_milliSeconds = 0;
  int turnON_milliSeconds      = 100;
  int alarmON_milliSeconds     = 2000;
  int turnOFF_milliSeconds     = 4000;
  
  // beräknar antal millisekunder som alarmknappen är intryck
  while( digitalRead(BUTTON_ALARM_PIN) == 0 )
  {
    delay(100);
    pressLength_milliSeconds = pressLength_milliSeconds + 100;
  }
  
  //om alarmknappen är intryck längre än 4 sek, stängs av väckarklockan.
  if( pressLength_milliSeconds >= turnOFF_milliSeconds )
      {
        seconds = seconds + 5;
        alarmON = false;
        displayTimeLCD(hours, minutes, seconds, 0, 0, "TIME: ", ' ');
        delay(1000);
      }  
  
  //om alarmknappen är intryck mindre än 2 sek, sätts alarm-inställning igång.
  else if( pressLength_milliSeconds >= turnON_milliSeconds )
  {
    seconds++;
    lcd.clear();
    displayTimeLCD(alarmHours, alarmMinutes, alarmSeconds, 0, 0, "TIME: ", ' ');
    displayMessageLCD(0, 1, "ALARM SETTING");
    larmExecuting = true;
     
    do 
    {
        //ställer in alarmets timmar och minuter
        timeSetting("alarmTime");
           
        // beräknar antal millisekunder som alarmknappen är intryck
        while( digitalRead(BUTTON_ALARM_PIN) == 0 )
        {
            delay(100);
            pressLength_milliSeconds = pressLength_milliSeconds + 100;
        }

        //om alarmknappen är intryck längre än 4 sek, stängs av väckarklockan.
        if( pressLength_milliSeconds >= turnOFF_milliSeconds )
        {
            seconds = seconds + 8;
            alarmON = false;
            displayTimeLCD(hours, minutes, seconds, 0, 0, "TIME: ", ' ');
            delay(1200);
            larmExecuting = false;
        } 
        // om alarmknappen är intryck längre än 2 sek och mindre än 4 sek, aktiveras alarmet. 
        else if( pressLength_milliSeconds >= alarmON_milliSeconds )
        {
            seconds = seconds + 8;
            alarmON = true;
            displayTimeLCD(hours, minutes, seconds, 0, 0, "TIME: ", 'A');
            delay(1200);
            larmExecuting = false;        
        }
    } while(larmExecuting);    
    lcd.clear();
  }
}

/*********************************************************************
* Funktionen kontrollerar alarmets tid är samma som klockans tid.
**********************************************************************/
void checkAlarm()
{
  alarmIsGoing = false;
  int pressLength_milliSeconds = 0;
  int turnOFF_milliSeconds     = 4000;
  
  //om alarmtiden stämmer med klockans tid och larmet är påsatt, går larmet igång.
  if( alarmHours == hours && alarmMinutes == minutes && 
      alarmSeconds == seconds && alarmON == true )
  {
      alarmIsGoing = true;
      lcd.clear();
      displayMessageLCD(4, 0, "WAKE UP!");
      activateRGB();
      do
      {
          playAlarm("ON");

          //medan larm-knappen är intryck lagras millisekunderna i en variabel.
          while( digitalRead(BUTTON_ALARM_PIN) == 0 )
          {
              delay(100);
              pressLength_milliSeconds = pressLength_milliSeconds + 100;
          }

          //om larmknappen är intryck längre än 4 sekunder, stängs av väckarklockan.
          if( pressLength_milliSeconds >= turnOFF_milliSeconds )
          {
            playAlarm("OFF");
            alarmON = false;
            lcd.clear();
            delay(100);
            seconds = seconds + 8;
            alarmIsGoing = false;     
          }
      } while(alarmIsGoing);
      return;
  }
}
            
/***********************************************************
* Funktionen spelar en melodi när väckarklockan går igång. 
************************************************************/
void playAlarm(String mode)
{
  // tonerna i melodin: 
  #define NOTE_C4  262
  #define NOTE_G3  196
  #define NOTE_A3  220
  #define NOTE_B3  247
  int melody[] = {262, 196, 196, 220, 196, 0, 247, 262};

  int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4}; //tonens längd: 4 = kvarton, 8 = åttonde ton.
  const int BUZZER_PIN = A1;
  
  if(mode == "ON") {
    for (int thisNote = 0; thisNote < 8; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(BUZZER_PIN, melody[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(BUZZER_PIN);
    }
  }
  else{
      noTone(BUZZER_PIN);
      delay(500);
  }
}

/***********************************************************
* Funktionen hanterar RGB-lysdioden. 
************************************************************/
void activateRGB()
{
  if( alarmIsGoing == true )
  {
    // Röd
    Serial.println("RED");
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    delay(10);
  }
  else if( degreesCelsius > 29 && degreesCelsius < 45)    
  {
    // Gul
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
        
    delay(10);
  }
  else 
  {
    // Grön
    Serial.println("GREEN"); 
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    delay(10);
  }
}

/***********************************************************
* Funktionen beräknar och visar rumtemperaturen. 
************************************************************/
void displayTemperature()
{
  //Mäter spänningen vid det analoga stiftet
  float voltage = (analogRead(TEMPERATURE_PIN) * 0.004882814);

  //Omvandlar spänningen till grader Celsius
  degreesCelsius = (voltage - 0.5) * 100.0; 
  
  String degrees = String(degreesCelsius,1); 
  String sign    = String((char)178);
  String temperature = String("TEMP: " + degrees + sign + "C");
    
  //Visar temperaturen på LCD-displayen
  displayMessageLCD(0, 1, temperature );
}

/***********************************************************
* Funktionen hanterar och visar datum 
************************************************************/
void displayDate()
{ 
  String fullDate = String(currentDay + " " + currentDate); 
  displayMessageLCD(0, 1, fullDate );
}

/***********************************************************
* Funktionen hanterar och visar datum 
************************************************************/
void displayTempOrDate()
{
  if ( digitalRead(BUTTON_TEMP_DATE_PIN) == 0 ) displayDate();
  else displayTemperature();
}
