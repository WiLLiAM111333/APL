/***************************************************************************************
 * Projekt 14 - DC-Motor -övning 2
 * 
 * LÖPANDE BAND
 * Denna övning simulerar ett löpandeband som transporterar paket från ena sidan av  
 * fabriken till den andra. Med en krets som består av en knapp för att starta remmen  
 * och en slutstegssensor för att stoppa löpandetbandet och kunna lossa paketen.
 * Målen är:
 *   • Starta löpandebandet endast med startknappen, röd lampa tänds och ett ljud avges.
 *  • Stoppa löpandebandet när det behövs med stopp-knappen. En grön lampa tänds. 
 ****************************************************************************************/

const int PIN_MOTOR       = 9; 
const int PIN_STOP_MOTOR  = 3;
const int PIN_START_MOTOR = 4;
const int PIN_LED_GREEN   = 5;
const int PIN_LED_RED     = 6;
const int PIN_BUZZER      = A1;

bool state = 0;
bool buzzerPlaying = true;

void setup()
{
    pinMode(PIN_STOP_MOTOR,  INPUT_PULLUP); 
    pinMode(PIN_START_MOTOR, INPUT_PULLUP); 
    pinMode(PIN_MOTOR,      OUTPUT);
    pinMode(PIN_LED_GREEN,  OUTPUT);
    pinMode(PIN_LED_RED,    OUTPUT);
}

void loop()
{
    int startValue = digitalRead(PIN_START_MOTOR); //start-knappens status/tillstånd läses av.  
    int stopValue  = digitalRead(PIN_STOP_MOTOR);  //stopp-knappens status/tillstånd läses av. 
   
    if (startValue == LOW)  //Om värdet på den lokala variabeln "startValue" är lågt, 0. 
    {             
        delay(500); 
        state = 1;            //ändras tillståndet till 1 för att aktivera motorn. 
    }
  
    if (stopValue == LOW)   //Om värdet på den lokala variabeln "stopValue" är lågt, 0.
    {                             
        state = 0;            //ändras tillståndet till 0 för att stänga av motorn 
    }
    
  
    if(state == 0)          // Om värdet för "status/tillstånd" är 0, stängs av motorn. 
    {
        digitalWrite (PIN_LED_GREEN, HIGH);
        digitalWrite (PIN_LED_RED, LOW);
        digitalWrite (PIN_MOTOR, LOW); 
        buzzerPlaying = true; 
    }
    else    // annars sätts motorn på.        
    {
        digitalWrite (PIN_MOTOR, HIGH);
        digitalWrite (PIN_LED_GREEN, LOW);
        digitalWrite (PIN_LED_RED, HIGH);
        
        if( buzzerPlaying == true )
        {
            playBuzzer();
            buzzerPlaying = false; 
        }    
    }
}


void playBuzzer()
{
    tone(PIN_BUZZER, 490); //Skapar en ton(ljud)
    delay(450);
    noTone(PIN_BUZZER);    //stänger av ljudet.
    delay(150);
    tone(PIN_BUZZER, 490); //Skapar en ton(ljud)
    delay(350);
    noTone(PIN_BUZZER);    //stänger av ljudet.
    delay(100);
    tone(PIN_BUZZER, 490); //Skapar en ton(ljud)
    delay(250);
    noTone(PIN_BUZZER);    //stänger av ljudet.
}
 
