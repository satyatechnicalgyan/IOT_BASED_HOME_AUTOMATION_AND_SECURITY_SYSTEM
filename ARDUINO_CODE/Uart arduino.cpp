#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial nodemcu(2,3);

// Connect VCC of the BMP180 / BMP085 sensor to 3.3V
// Connect GND to Ground

long int data; 
int relay1 = 13; 
int relay2 = 14;

void setup()
{
Serial.begin(9600); 
nodemcu.begin(9600);
pinMode(relay1, OUTPUT); 
pinMode(relay2, OUTPUT);




}

void loop()
{
  

if ( nodemcu.available() > 0 ) 
{
  data = nodemcu.parseInt();
  delay(100); 
  Serial.println(data); 

  if ( data == 10 )
  {
    digitalWrite(relay1, LOW); 
  }

    if ( data == 11 )
  {
    digitalWrite(relay1, HIGH); 
  }

  // relay2 

    if ( data == 12 )
  {
    digitalWrite(relay2, LOW); 
  }

    if ( data == 13 )
  {
    digitalWrite(relay2, HIGH); 
  }
}



}
