#ifndef MESO_H
#define MESO_H

typedef struct {
    int id;
    char naziv[50];
    float cijena;
    float kolicina;
} Meso;

// funkcije
void dodajMeso();
void ispisiMeso();
void urediMeso();
void obrisiMeso();

#endif
