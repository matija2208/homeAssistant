#define UBRR3H
#include <Arduino.h>
#include <HardwareSerial.h>

#define relej 2

void setup()
{
  pinMode(relej, OUTPUT);
  Serial3.begin(9600);
}

void loop()
{
  int a = Serial3.read();
  if(a!=-1)
  {
    if (a == 49)
    {
      digitalWrite(relej, HIGH);
    }
    else if(a==48)
    {
      digitalWrite(relej, LOW);
    }
  }
    
}
