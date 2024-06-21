#ifndef STRANICA_H
#define STRANICA_H

const char *stranica = "<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>Home</title>\
    <script src=\"https://cdn.jsdelivr.net/npm/axios/dist/axios.min.js\"></script>\
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
    <script>\
        const link = 'http://192.168.1.27';\
        async function dugme(d)\
        {\
            let id=d.id;\
            let vrednost=(d.value===\"1\")?0:1;\
            let k=document.getElementById(id);\
            k.value=vrednost;\
            let t=k.style.backgroundColor;\
            k.style.backgroundColor=k.style.color;\
            k.style.color=t;\
            k.innerText=(k.value===\"1\")?\"Upaljeno\":\"Ugaseno\";\
            try\
            {\
                let podaci = new FormData();\
                podaci.append(\"id\",id);\
                podaci.append(\"vrednost\",vrednost);\
                let msg = await axios.post(link+'/relej', podaci);\
                console.log(msg);\
            }\
            catch(err)\
            {\
                console.log(err);\
            }\
        }\
        async function ucitaj()\
        {\
            let poruka;\
            Promise.resolve(axios.get(link + \"/releji\")).then((value)=>{\
                poruka=value.data;\
                console.log(poruka);\
                let releji = poruka;\
                console.log(releji);\
                let div =``;\
                for (let i = 0; i < releji.length; i++)\
                {\
                    div += `\
                    <div class =\"stavka\">\
                        <label for=\"${releji[i].id}\" class=\"labela\">${releji[i].ime}</label>\
                        <button class=\"dugme\" id = \"${releji[i].id}\" onclick=\"dugme(this)\" value=${releji[i].vrednost} style=\"color:${(releji[i].vrednost)?\"#222\":\"#AAA\"}; background-color: ${(releji[i].vrednost)?\"#AAA\":\"#222\"};\">${(releji[i].vrednost)?\"Upaljeno\":\"Ugaseno\"}</button>\
                    </div>`;\
                }\
                console.log(div);\
                document.getElementById('paleta').innerHTML = div;\
            });\
        }\
    </script>\
</head>\
<body onload=\"ucitaj()\">\
    <div id=\"paleta\"></div>\
    \
</body>\
</html>";

#endif