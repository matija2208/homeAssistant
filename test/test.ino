#define UBRR3H
#include <Arduino.h>
#include <HardwareSerial.h>
#include "Strukture.h"
#include "Releji.h"

void setup()
{
    Serial3.begin(115200);
    Serial.begin(9600);
    for (int i = 0; i < NReleji;i++)
    {
        pinMode(Releji[i].pin, OUTPUT);
    }
}

bool msg = false;
bool cmd = false;

void loop()
{
  int a = Serial3.read();
  if(a!=-1)
  {
    if(a=='\001')
        msg = true;
    else if(a=='\002')
        cmd = true;
    else if(a=='\003')
        cmd = false;
    else if(msg)
    {
        if(a=='\004')
        {
            msg=false;
        }
        else
        {
            Serial.print(char(a));
        }
    }
    else if(cmd)
    {

        Relej r;
        r.id = (char *)malloc(sizeof(char));
        r.id[0] = char(a);
        int i = 1;
        while(a=Serial3.read(),a!=':')
        {
            if(a!=-1)
            {
                r.id = (char *)realloc(r.id, sizeof(char) * (i + 1));
                r.id[i] = char(a);
                i++;
            }
        }
        r.id = (char *)realloc(r.id, sizeof(char) * (i + 1));
        r.id[i] = '\0';
        while(a=Serial3.read(),a==-1);
        r.vrednost = a - 48;

        for (int i = 0; i < NReleji; i++)
        {
            if(!strcmp(Releji[i].id,r.id))
            {
                
                digitalWrite(Releji[i].pin, r.vrednost);
                break;
            }
        }
        free(r.id);
    }
    // else
    //     Serial.print(char(a));
  }
    
}
