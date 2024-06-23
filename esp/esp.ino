#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include "Strukture.h"
#include "Stranica.h"

#ifndef STASSID
#define STASSID "TS-E8Jy"
#define STAPSK "632mdpfY"
#endif

#define USR "matija"
#define PSWD "01061944"

ESP8266WebServer server(80);

void pocetna(){
    if(!server.authenticate(USR,PSWD))
        return server.requestAuthentication();
    server.send(200, "text/html", stranica);
}

void vratiReleje()
{
    if(server.arg("pageId")=="01061944mM\\")
    {
        String releji = "\005releji\006";
        Serial.print(releji);
        int a;
        while(a=Serial.read(),a==-1)
            ;
        releji = Serial.readStringUntil('\006');
        server.send(200, "text/plain", releji);
    }
    else
    {
        server.send(403);
    }
    
}

void relej()
{
    Relej r;

    int n = server.args();
    if(n==3 && server.arg("pageId")=="01061944mM\\")
    {
        r.id = server.arg("id").c_str();

        r.vrednost = atoi(server.arg("vrednost").c_str());

        String poruka = "\002";
        poruka += r.id;
        poruka += ":";
        poruka += String(r.vrednost);
        poruka +="\003";
        Serial.print(poruka);
        
        server.send(200, "text/plain", poruka);
    }
    else
    {
        server.send(403);
    }

    
}

void handleNotFound()
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";

    for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }

    server.send(404, "text/plain", message);
}

const char *ssid = STASSID;
const char *password = STAPSK;

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");
    delay(3000);
    Serial.println("\001Connecting to Wi-Fi: ");
    delay(1);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    Serial.print("\nConnected.\nIP: ");
    Serial.println(WiFi.localIP());
    Serial.print('\004');
    delay(1);
    ArduinoOTA.begin();
    server.enableCORS(true);
    server.on("/",HTTP_GET, pocetna);
    server.on("/relej",HTTP_PUT, relej);
    server.on("/releji",HTTP_GET, vratiReleje);
    server.onNotFound(handleNotFound);
    server.begin();
}

void loop()
{
    ArduinoOTA.handle();
    server.handleClient();
}