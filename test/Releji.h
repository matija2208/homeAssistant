#ifndef RELEJI_H
#define RELEJI_H

typedef struct{
    const char *id;
    int pin;
} TabelaReleja;

const int NReleji = 1;
const TabelaReleja Releji[] = {
    {"relej1", 2}
};

#endif