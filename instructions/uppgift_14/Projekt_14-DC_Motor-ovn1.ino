/***************************************************************************************
 * Projekt 14 - DC-Motor -övning 1
 * 
 * LÖPANDE BAND
 * Denna övning simulerar ett löpandeband som transporterar paket från ena sidan av  
 * fabriken till den andra. Med en krets som består av en knapp för att starta remmen  
 * och en slutstegssensor för att stoppa löpandetbandet och kunna lossa paketen.
 * Målen är:
 *    • Starta löpandebandet endast med startknappen.
 *    • Stoppa löpandebandet endast med stoppknappen, när det behövs.
 ***************************************************************************************/

const int PIN_MOTOR = 9; 
const int PIN_START_MOTOR = 6; 
const int PIN_STOP_MOTOR  = 3;

bool state = 0;

void setup()
{
  pinMode(PIN_STOP_MOTOR,  INPUT_PULLUP); 
  pinMode(PIN_START_MOTOR, INPUT_PULLUP); 
  pinMode(PIN_MOTOR, OUTPUT); 
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
    digitalWrite (PIN_MOTOR, LOW);
  }
  else                   // annars sätts motorn på.        
  { 
    digitalWrite (PIN_MOTOR, HIGH); 
  }
}
 
