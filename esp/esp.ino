#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
}

int a = 1;
void loop()
{
    int t = millis();
    if(a!=-1)
    {
        Serial.write(char(a+48));
    }
    a = (a) ? 0 : 1;
    while(millis()-t<1000)
        delay(0);
}