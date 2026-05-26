#ifndef MESO_H
#define MESO_H

#define MAX_NAZIV 50
typedef struct {
    int id;
    char naziv[MAX_NAZIV];
    float cijena;
    float kolicina;
} Meso;



void dodajMeso();
void ispisiMeso();
void ispisiRekurzivno(FILE* fp);
void urediMeso();
void obrisiMeso();
void sortirajPoCijeni();
void pretraziMeso();

static inline float vrijednost(Meso m) {
    return m.cijena * m.kolicina;
}

#endif