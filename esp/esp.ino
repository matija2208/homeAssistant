#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Strukture.h"

#ifndef STASSID
#define STASSID "TS-E8Jy"
#define STAPSK "632mdpfY"
#endif

ESP8266WebServer server(80);

void pocetna()
{
    const char *stranica =
    "<!DOCTYPE html>\
    <html lang=\"en\">\
    <head>\
        <meta charset=\"UTF-8\">\
        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
        <title>Home</title>\
        <style>\
            body {\
                font-family: 'Consolas', monospace;\
                margin: 0;\
                padding: 0;\
                background-color: #444444;\
                }\
            .dugme{\
                margin:5px;\
                border-radius: 10%;\
                font-family: 'Consolas',monospace;\
                background-color: #222222;\
                color: #AAAAAA;\
            }\
            .stavka{\
                background-color: #333333;\
                border-radius: 10%;\
                padding: 10px;\
                margin: 10px;\
                border-color: #000;\
                border-width: 2px;\
                width:30vh;\
                align-items: center;\
                display: flex;\
            }\
        </style>\
    </head>\
    <body>\
        <div class=\"stavka\">\
            <label for=\"relej1\" class=\"labela\">RELEJ 1</label>\
            <button class=\"dugme\" id = \"relej1\" onclick=\"dugme(this)\" value=0 style=\"color:#AAAAAA; background-color: #222222;\">Ugaseno</button>\
        </div>\
        \
        <script src=\"https://cdn.jsdelivr.net/npm/axios/dist/axios.min.js\"></script>\
        <script>\
            async function dugme(d)\
            {\
                let id=d.id;\
                let vrednost=(d.value===\"1\")?0:1;\
    \
                let k=document.getElementById(id);\
                k.value=vrednost;\
                let t=k.style.backgroundColor;\
                k.style.backgroundColor=k.style.color;\
                k.style.color=t;\
                \
                k.innerText=(k.value===\"1\")?\"Upaljeno\":\"Ugaseno\";\
                \
                try\
                {\
                    let podaci = new FormData();\
                    podaci.append(\"id\",id);\
                    podaci.append(\"vrednost\",vrednost);\
                    let msg = await axios.post('./relej', podaci);\
                    console.log(msg);\
                }\
                catch(err)\
                {\
                    console.log(err);\
                }\
            }\
        </script>\
    </body> \
    </html>";
    server.send(200, "text/html", stranica);
}

void relej()
{
    Relej r;

    int n = server.args();
    if(n==2)
    {
        r.id = server.arg(0).c_str();

        r.vrednost = atoi(server.arg(1).c_str());

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
        server.send(400, "text/plain", "Pogresan broj argumenata!");
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
    server.on("/", pocetna);
    server.on("/relej", relej);
    server.onNotFound(handleNotFound);
    server.begin();
}

void loop()
{
    server.handleClient();
}