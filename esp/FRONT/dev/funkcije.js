const link = 'http://192.168.1.27';
const pageId = '01061944mM\\';
async function ucitaj()
{
    let poruka;
    Promise.resolve(axios.get(link + "/releji?pageId="+pageId)).then((value)=>{
        poruka=value.data;
        console.log(poruka);
        let releji = poruka;
        console.log(releji);
        let div =``;
        for (let i = 0; i < releji.length; i++)
        {
            div += `
            <div class ="stavka" style="color:${(releji[i].vrednost)?"#333":"#999"}; background-color: ${(releji[i].vrednost)?"#999":"#333"};">
                <label for="${releji[i].id}" class="labela" style="color:${(releji[i].vrednost)?"#333":"#999"}">${releji[i].ime}</label>
                <button class="dugme" id = "${releji[i].id}" onclick="dugme(this)" value=${releji[i].vrednost} style="color:${(releji[i].vrednost)?"#222":"#AAA"}; background-color: ${(releji[i].vrednost)?"#AAA":"#222"};">${(releji[i].vrednost)?"Upaljeno":"Ugaseno"}</button>
            </div>`;
        }
        console.log(div);
        document.getElementById('paleta').innerHTML = div;
    });
}
async function dugme(d)
{
    let id=d.id;
    let vrednost=(d.value==="1")?0:1;
    let k=document.getElementById(id);
    try
    {
        let podaci = new FormData();
        podaci.append("id",id);
        podaci.append("vrednost",vrednost);
        podaci.append("pageId",pageId);
        let msg = await axios.put(link+'/relej', podaci);
        console.log(msg);
        ucitaj();
    }
    catch(err)
    {
        console.log(err);
    }
}