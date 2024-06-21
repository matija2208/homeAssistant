#ifndef RELEJI_H
#define RELEJI_H

typedef struct{
    const char *id;
    int pin;
    const char *name;
} TabelaReleja;

const int NReleji = 2;
const TabelaReleja Releji[] = {
    {"relej1", 2, "RELEJ 1"},
    {"relej2",3, "RELEJ 2"}
};
int VReleji[] = {0,0};

#endif