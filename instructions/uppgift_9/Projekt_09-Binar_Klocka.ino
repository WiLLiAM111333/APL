/***********************************************
*  Projekt 9 - Binär klocka
************************************************/

int seconds = 0;
int minutes = 59;
int hours   = 15;

int ledPinsSec[] = {2, 3, 4, 5, 6, 7};
int ledPinsMin[] = {8, 9, 10, 11, 12, 13};
int ledPinsHr[]  = {14, 15, 16, 17, 18, 19};
//int ledPinsHr[]  = {A0, A1, A2, A3, A4};

int secSize  = sizeof(ledPinsSec) / sizeof(int);
int minSize  = sizeof(ledPinsMin) / sizeof(int);
int hourSize = sizeof(ledPinsHr)  / sizeof(int);

void setup()
{
    for(int i = 0; i< secSize;i++)
    {
      pinMode(ledPinsSec[i], OUTPUT);
    }

    for(int i = 0; i< minSize;i++)
    {
        pinMode(ledPinsMin[i], OUTPUT);
    }

    for(int i = 0; i< hourSize;i++)
    {
        pinMode(ledPinsHr[i], OUTPUT);
    }
  
    Serial.begin(9600);
    Serial.println();
    Serial.println("-----------------------------------------");
    Serial.println("The binary clock is starting to tick now:");
    Serial.println("-----------------------------------------");
}

void loop() 
{
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
  
    Serial.print("Hours: ");
    Serial.print(hours);
    Serial.print(" Minutes: ");
    Serial.print(minutes);
    Serial.print(" Seconds: ");
    Serial.println(seconds);
  
    DisplaySeconds();
    DisplayMinutes();
    DisplayHours();
  
    delay(1000);  
}

// Omvandlar SEKUNDERNA från det decimala till binära systemet.
void DisplaySeconds()
{     
  for(int i = secSize - 1; i>= 0; i--)
  {
    int currentSecond = bitRead(seconds, i);
    digitalWrite(ledPinsSec[i], currentSecond); 
  }  
}

// Omvandlar MINUTERNA från det decimala till binära systemet.
void DisplayMinutes()
{     
  for(int i = minSize - 1; i>= 0; i--)
  {
    int currentMinute = bitRead(minutes, i);
    digitalWrite(ledPinsMin[i], currentMinute); 
  }  
}


void DisplayHours()
{     
  for(int i = hourSize - 1; i>= 0; i--)
  {
    int currentHour = bitRead(hours, i);
    digitalWrite(ledPinsHr[i], currentHour); 
  }  
}
