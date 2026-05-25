#ifndef MESO_H
#define MESO_H
//2 3 4
typedef struct {
    int id;
    char naziv[50];
    float cijena;
    float kolicina;
} Meso;

// funkcije (12 19)
void dodajMeso();
void ispisiMeso();
void ispisiRekurzivno(FILE* fp);
void urediMeso();
void obrisiMeso();
void sortirajPoCijeni();
void pretraziMeso();

#endif