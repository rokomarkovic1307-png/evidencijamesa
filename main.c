#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char naziv[50];
    float cijena;
    float kolicina;
} Meso;

// FUNKCIJE
void dodajMeso();
void ispisiMeso();
void urediMeso();
void obrisiMeso();

int main() {

    //IZBORNIK

    int izbor;

    do {

        printf("\n===== EVIDENCIJA MESA =====\n");
        printf("||--1. Dodaj meso\n--||");
        printf("||--2. Ispisi meso\n--||");
        printf("||--3. Uredi meso\n--||");
        printf("||--4. Obrisi meso\n--||");
        printf("||--0. Izlaz\n--||");
        printf("Odabir: ");

        scanf("%d", &izbor);

        switch (izbor) {

        case 1:
            dodajMeso();
            break;

        case 2:
            ispisiMeso();
            break;

        case 3:
            urediMeso();
            break;
        case 4:
            obrisiMeso();
            break;
        case 0:
            printf("Izlaz iz programa.\n");
            break;

        default:
            printf("Neispravan unos!\n");
        }

    } while (izbor != 0);

    return 0;
}

//DODAVANJE MESA
void dodajMeso() {

    FILE* fp = fopen("meso.dat", "ab");

    if (fp == NULL) {
        perror("Greska pri otvaranju datoteke");
        return;
    }

    Meso m;

    printf("Unesi ID: ");
    scanf("%d", &m.id);

    printf("Unesi naziv: ");
    scanf("%49s", m.naziv);

    printf("Unesi cijenu: ");
    scanf("%f", &m.cijena);

    printf("Unesi kolicinu (kg): ");
    scanf("%f", &m.kolicina);

    if (fwrite(&m, sizeof(Meso), 1, fp) != 1) {
        perror("Greska pri upisu");
    }
    else {
        printf("Meso uspjesno dodano!\n");
    }

    fclose(fp);
}

//ISPIS MESA
void ispisiMeso() {

    FILE* fp = fopen("meso.dat", "rb");

    if (fp == NULL) {
        perror("Greska pri otvaranju datoteke");
        return;
    }

    Meso m;

    printf("\n===== POPIS MESA =====\n");

    while (fread(&m, sizeof(Meso), 1, fp) == 1) {

        printf("\nID: %d", m.id);
        printf("\nNaziv: %s", m.naziv);
        printf("\nCijena: %.2f €", m.cijena);
        printf("\nKolicina: %.2f kg\n", m.kolicina);
    }

    fclose(fp);
}

//UREDIVANJE MESA
void urediMeso() {

    FILE* fp = fopen("meso.dat", "rb+");

    if (fp == NULL) {
        perror("Greska pri otvaranju datoteke");
        return;
    }

    int trazeniID;
    int pronaden = 0;

    Meso m;

    printf("Unesi ID mesa za izmjenu: ");
    scanf("%d", &trazeniID);

    while (fread(&m, sizeof(Meso), 1, fp) == 1) {

        if (m.id == trazeniID) {

            printf("Novi naziv: ");
            scanf("%49s", m.naziv);

            printf("Nova cijena: ");
            scanf("%f", &m.cijena);

            printf("Nova kolicina: ");
            scanf("%f", &m.kolicina);

            fseek(fp, -sizeof(Meso), SEEK_CUR);
            fwrite(&m, sizeof(Meso), 1, fp);
            printf("Meso uspjesno uredeno!\n");
            pronaden = 1;
            break;
        }
    }

    if (!pronaden) {
        printf("Meso nije pronadeno!\n");
    }

    fclose(fp);

}
//BRISANJE MESA
void obrisiMeso() {
    FILE* fp = fopen("meso.dat", "rb");
    FILE* temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp==NULL) {
        printf("Greska pri otvaranju");
        return;
    }
    int trazeniID;
    int pronaden;
    Meso m;
    printf("Unesi ID mesa za brisanje:");
    scanf("%d", &trazeniID);
    
    while (fread(&m, sizeof(Meso), 1, fp) == 1) {
        if (m.id == trazeniID) {
            pronaden = 1;
            continue;
        }
    fwrite(&m, sizeof(Meso), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    remove("meso.dat");
    rename("temp.dat", "meso.dat");

    if (pronaden) {
        printf("Meso uspjesno obrisano!\n");
    }
    else {
        printf("Meso nije pronadeno!\n");
    }

}
