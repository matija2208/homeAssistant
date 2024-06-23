#include <stdio.h>
#include <stdlib.h>

int main()
{
    const char *htmlF = "index.html";
    const char *hF = "Stranica.h";

    FILE *html = fopen(htmlF, "r");
    FILE *h = fopen(hF, "w");

    fprintf(h, "#ifndef STRANICA_H\n#define STRANICA_H\n\nconst char *stranica = \"");

    char c;
    while(c=getc(html),c!=EOF)
    {
        if(c=='\n')
            fprintf(h, "\\\n");
        else if(c=='"')
            fprintf(h, "\\\"");
        else if(c=='\\')
            fprintf(h, "\\\\");
        else
            fprintf(h, "%c", c);
    }
    fprintf(h, "\";\n\n#endif");

    fclose(html);
    fclose(h);
}