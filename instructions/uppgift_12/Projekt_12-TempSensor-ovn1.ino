/**********************************************************************
* Projekt 12 - TEMPERATUR SENSOR - ovn 1
* Använd fönstret "seriell monitor" för att läsa en temperatursensor. 
**********************************************************************/
  
const int TEMPERATURE_PIN = A0;
const float START_TEMP = 20.0;

void setup()
{
  Serial.begin(9600); // öppna en seriell port
  
    for(int pinNumber = 2; pinNumber < 5; pinNumber++)
    {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  } 
}


void loop(){
  int sensorValue = analogRead(TEMPERATURE_PIN);
  
    Serial.print("Sensor Value: "); 
    Serial.print(sensorValue);
  
    // omvandlar ADC-avläsningen till spänning
  float voltage = (sensorValue/1024.0) * 5.0;
    
    // omvandlar spänningen till temperatur i grader
  float degreesCelsius = (voltage - .5) * 100;
  
    Serial.print(", Volts: ");
  Serial.print(voltage);
  
    Serial.print(", degrees Celsius: ");
  Serial.print(degreesCelsius);
  
    Serial.print(", START_TEMP: ");
  Serial.println(START_TEMP);
  
    if(degreesCelsius < START_TEMP)
    {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    }
    else if( degreesCelsius >= START_TEMP + 2 && 
              degreesCelsius <  START_TEMP + 4)
    {      
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
    }
    else if( degreesCelsius >= START_TEMP + 4 && 
        degreesCelsius <  START_TEMP + 6)
    {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    }
    else if(degreesCelsius >= START_TEMP + 6)
    {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    }
  
  delay(1000);
} 
