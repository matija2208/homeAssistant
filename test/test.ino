#define UBRR3H
#include <Arduino.h>
#include <HardwareSerial.h>
#include "Strukture.h"
#include "Releji.h"

void setup()
{
    Serial3.begin(115200);
    Serial.begin(9600);
    for (int i = 0; i < NReleji; i++)
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
    if(a=='\005')
    {

        String enq = "";
        while (a=Serial3.read(),a!='\006')
        {
            if(a==-1)
                continue;
            enq += char(a);
        }
        Serial.println(enq);
        if(enq == "releji")
        {
            String r = "[";
            for (int i = 0; i < NReleji; i++)
            {
                r += "{\"id\":\"";
                r += Releji[i].id;
                r += "\",\"vrednost\":";
                r += String(VReleji[i]);
                r += ",\"ime\":\"";
                r += Releji[i].name;
                r += "\"}";
                if(i!=NReleji-1)
                {
                    r+=",";
                }
            }
            r += "]";
            Serial3.print('\005');
            Serial3.print(r);
            Serial3.print('\006');
            Serial.println(r);
        }
    }
    else if(a=='\001')
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
            if(!strcmp(Releji[i].id, r.id))
            {
                VReleji[i] = r.vrednost;
                digitalWrite(Releji[i].pin, r.vrednost);
                break;
            }
        }
        free(r.id);
    }
  }
    
}
