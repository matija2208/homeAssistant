#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv)
{
    if(argc==1)
    {
        printf("Usage: %s <filenames>\n", argv[0]);
        return 1;
    }

    int i;
    const char *outF = "../Stranice.h";
    FILE *out = fopen(outF, "w");

    fprintf(out, "#ifndef STRANICE_H\n#define STRANICE_H\n\n");

    for (i = 1; i < argc;i++)
    {
        char *filename = argv[i];
        FILE *in = fopen(filename, "r");

        char def[1000];
        int ext = strlen(argv[i]) - 1;
        while(argv[i][ext]!='.')
            ext--;

        int j;
        for (j = 0; j < ext;j++)
        {
            def[j] = toupper(argv[i][j]);
        }
        def[ext] = '\0';

        fprintf(out, "const char *%s = \"", def);

        char c;
        while(c=getc(in),c!=EOF)
        {
            if(c=='\n')
                fprintf(out, "\\\n\\n");
            else if(c=='"')
                fprintf(out, "\\\"");
            else if(c=='\\')
                fprintf(out, "\\\\");
            else
                fprintf(out, "%c", c);
        }
        fprintf(out, "\";\n\n");

        fclose(in);
    }

    fprintf(out, "const char* vratiStranicu(const char* putanja)\n{\n");
    for (i = 1; i < argc;i++)
    {
        char def[1000];
        int ext = strlen(argv[i]) - 1;
        while(argv[i][ext]!='.')
            ext--;

        int j;
        for (j = 0; j < ext;j++)
        {
            def[j] = toupper(argv[i][j]);
        }
        def[ext] = '\0';
        if(i==1)
        {
            fprintf(out, "\tif");
        }
        else
        {
            fprintf(out, "\telse if");
        }
        if(!strcmp("index.html",argv[i]))
            fprintf(out, "(!strcmp(putanja,\"%s\") || !strcmp(putanja,\"\"))\n\t\treturn %s;\n", argv[i], def);
        else
            fprintf(out, "(!strcmp(putanja,\"%s\"))\n\t\treturn %s;\n", argv[i], def);
    }
    fprintf(out, "\telse return \"404 not found\";\n}\n\n#endif");
    fclose(out);
}