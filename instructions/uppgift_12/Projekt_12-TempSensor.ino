/*********************************************************************
* Projekt 12 - TEMPERATUR SENSOR
* Använd fönstret "seriell monitor" för att läsa en temperatursensor. 
**********************************************************************/

// använder den analoga ingången A0 för att mäta 
// temperaturgivarens signalstift. 
const int TEMPERATURE_PIN = A0;


void setup()
{
  Serial.begin(9600); 
}


void loop()
{
  // Deklarerar 3 variabler som ett heltal med decimaler.
  float voltage, degreesCelsius, degreesFahrenheit;

  // Mäter spänningen vid det analoga stiftet
  voltage = getVoltage(TEMPERATURE_PIN); 

  // Omvandlar spänningen till grader Celsius
  degreesCelsius = (voltage - 0.5) * 100.0;  

  // Onvandlar grader Celsius till Fahrenheit
  degreesFahrenheit = degreesCelsius * (9.0 / 5.0) + 32.0;
  
  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("  degrees celsius: ");
  Serial.print(degreesCelsius);
  Serial.print("  degrees Fahrenheit: ");
  Serial.println(degreesFahrenheit);

  delay(1000); //upprepa en gång per sekund (ändra som du vill!) 
}

/**********************************************************************
 * Funktionen omvandlar värdet 0 till 1023 som analogRead() returnerar, 
 * till ett 0,0 till 5,0-värde som är den sanna spänningen.
 ***********************************************************************/
float getVoltage(int pin)
{
    return (analogRead(pin) * 0.004882814); 
}
