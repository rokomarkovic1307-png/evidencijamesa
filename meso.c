#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "meso.h"

// DODAJ
void dodajMeso() {
    FILE* fp = fopen("meso.dat", "ab");
    if (!fp) return;

    Meso m;

    printf("ID: ");
    scanf("%d", &m.id);

    printf("Naziv: ");
    scanf("%49s", m.naziv);

    printf("Cijena: ");
    scanf("%f", &m.cijena);

    printf("Kolicina: ");
    scanf("%f", &m.kolicina);

    fwrite(&m, sizeof(Meso), 1, fp);
    fclose(fp);
}

// ISPIS
void ispisiMeso() {
    FILE* fp = fopen("meso.dat", "rb");
    if (!fp) return;

    Meso m;

    while (fread(&m, sizeof(Meso), 1, fp) == 1) {
        printf("\nID: %d", m.id);
        printf("\nNaziv: %s", m.naziv);
        printf("\nCijena: %.2f", m.cijena);
        printf("\nKolicina: %.2f\n", m.kolicina);
    }

    fclose(fp);
}

// UREDI
void urediMeso() {
    FILE* fp = fopen("meso.dat", "rb+");
    if (!fp) return;

    int id;
    int pronaden = 0;
    Meso m;

    printf("ID za urediti: ");
    scanf("%d", &id);

    while (fread(&m, sizeof(Meso), 1, fp) == 1) {
        if (m.id == id) {
            printf("Novi naziv: ");
            scanf("%49s", m.naziv);

            printf("Nova cijena: ");
            scanf("%f", &m.cijena);

            printf("Nova kolicina: ");
            scanf("%f", &m.kolicina);

            fseek(fp, -(long)sizeof(Meso), SEEK_CUR);
            fwrite(&m, sizeof(Meso), 1, fp);

            pronaden = 1;
            break;
        }
    }

    fclose(fp);

    if (!pronaden)
        printf("Nije pronadeno\n");
}

// IZBRISI
void obrisiMeso() {
    FILE* fp = fopen("meso.dat", "rb");
    FILE* temp = fopen("temp.dat", "wb");

    if (!fp || !temp) return;

    int id;
    int pronaden = 0;
    Meso m;

    printf("ID za brisanje: ");
    scanf("%d", &id);

    while (fread(&m, sizeof(Meso), 1, fp) == 1) {
        if (m.id == id) {
            pronaden = 1;
            continue;
        }
        fwrite(&m, sizeof(Meso), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("meso.dat");
    rename("temp.dat", "meso.dat");

    if (pronaden)
        printf("Obrisano!\n");
    else
        printf("Nije pronadeno!\n");


}