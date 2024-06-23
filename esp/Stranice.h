#ifndef STRANICE_H
#define STRANICE_H

const char *INDEX = "<!DOCTYPE html>\
\n<html lang=\"en\">\
\n<head>\
\n    <meta charset=\"UTF-8\">\
\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
\n    <title>Home</title>\
\n\
\n    <script src=\"https://cdn.jsdelivr.net/npm/axios/dist/axios.min.js\"></script>\
\n    <link rel=\"stylesheet\" href=\".?putanja=style.css\">\
\n    <script src=\".?putanja=funkcije.js\"></script>\
\n</head>\
\n<body onload=\"ucitaj()\">\
\n    <div id=\"paleta\"></div>\
\n</body>\
\n</html>";

const char *FUNKCIJE = "const link = '.';\
\nconst pageId = '01061944mM\\\\';\
\nasync function ucitaj()\
\n{\
\n    let poruka;\
\n    Promise.resolve(axios.get(link + \"/releji?pageId=\"+pageId)).then((value)=>{\
\n        poruka=value.data;\
\n        //console.log(poruka);\
\n        let releji = poruka;\
\n        //console.log(releji);\
\n        let div =``;\
\n        for (let i = 0; i < releji.length; i++)\
\n        {\
\n            div += `\
\n            <div class =\"stavka\" style=\"color:${(releji[i].vrednost)?\"#333\":\"#999\"}; background-color: ${(releji[i].vrednost)?\"#999\":\"#333\"};\">\
\n                <label for=\"${releji[i].id}\" class=\"labela\" style=\"color:${(releji[i].vrednost)?\"#333\":\"#999\"}\">${releji[i].ime}</label>\
\n                <button class=\"dugme\" id = \"${releji[i].id}\" onclick=\"dugme(this)\" value=${releji[i].vrednost} style=\"color:${(releji[i].vrednost)?\"#222\":\"#AAA\"}; background-color: ${(releji[i].vrednost)?\"#AAA\":\"#222\"};\">${(releji[i].vrednost)?\"Upaljeno\":\"Ugaseno\"}</button>\
\n            </div>`;\
\n        }\
\n        //console.log(div);\
\n        document.getElementById('paleta').innerHTML = div;\
\n    });\
\n}\
\nasync function dugme(d)\
\n{\
\n    let id=d.id;\
\n    let vrednost=(d.value===\"1\")?0:1;\
\n    //let k=document.getElementById(id);\
\n    try\
\n    {\
\n        let podaci = new FormData();\
\n        podaci.append(\"id\",id);\
\n        podaci.append(\"vrednost\",vrednost);\
\n        podaci.append(\"pageId\",pageId);\
\n        let msg = await axios.put(link+'/relej', podaci);\
\n        //console.log(msg);\
\n        ucitaj();\
\n    }\
\n    catch(err)\
\n    {\
\n        console.log(err);\
\n    }\
\n}";

const char *STYLE = "body {\
\n    font-family: 'Consolas', monospace;\
\n    margin: 0;\
\n    padding: 0;\
\n    background-color: #444444;\
\n    }\
\n.dugme{\
\n    margin:5px;\
\n    border-radius: 50%;\
\n    font-family: 'Consolas',monospace;\
\n    background-color: #222222;\
\n    color: #AAAAAA;\
\n    height: 40px;\
\n}\
\n.stavka{\
\n    background-color: #333333;\
\n    border-radius: 30%;\
\n    padding: 10px;\
\n    margin: 10px;\
\n    border-color: #000;\
\n    border-width: 2px;\
\n    width:200px;\
\n    height: 200px;\
\n    align-items: center;\
\n    text-align: center;\
\n    display:grid;\
\n}\
\n.labela{\
\n    text-align: center;\
\n    font-size: 18px;\
\n    font-family: 'Consolas',monospace;\
\n}\
\n#paleta{\
\n    display:flex;\
\n}";

const char* vratiStranicu(const char* putanja)
{
	if(!strcmp(putanja,"index.html") || !strcmp(putanja,""))
		return INDEX;
	else if(!strcmp(putanja,"funkcije.js"))
		return FUNKCIJE;
	else if(!strcmp(putanja,"style.css"))
		return STYLE;
	else return "404 not found";
}

#endif