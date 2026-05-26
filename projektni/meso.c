#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "meso.h"
#include "globals.h"

void dodajMeso() {
    FILE* fp = fopen(FILE_NAME, "ab");
    if (!fp) return;

    Meso m;

    printf("ID: ");
    scanf("%d", &m.id);

    //14
    if (m.id <= 0) {
        printf("Neispravan ID!\n");
        fclose(fp);
        return;

    }

    printf("Naziv: ");
    scanf("%49s", m.naziv);

    printf("Cijena: ");
    scanf("%f", &m.cijena);

    if (m.cijena <= 0) {
        printf("Neispravna cijena!\n");
        fclose(fp);

    }

    printf("Kolicina: ");
    scanf("%f", &m.kolicina);

    if (m.kolicina <= 0) {
        printf("Kolicina neispravna!\n");
        fclose(fp);

    }

    fwrite(&m, sizeof(Meso), 1, fp);
    fclose(fp);
}
static void ispisiNaslov() {
    printf("\n=====POPIS MESA======\n");
}

void ispisiMeso() {
    FILE* fp = fopen(FILE_NAME, "rb");
    if (!fp) return;

    Meso m;
    ispisiNaslov();
    while (fread(&m, sizeof(Meso), 1, fp) == 1) {
        printf("\n%d | %s | %.2f | %.2f | %.2f",
            m.id, m.naziv, m.cijena, m.kolicina,vrijednost(m));
    }

    fclose(fp);
}
void ispisiRekurzivno(FILE* fp) {

    Meso m;

    if (fread(&m, sizeof(Meso), 1, fp) != 1)
        return; // STOP uvjet

    printf("\n%d | %s | %.2f | %.2f",
        m.id, m.naziv, m.cijena, m.kolicina);

    ispisiRekurzivno(fp);
}

void urediMeso() {
    FILE* fp = fopen(FILE_NAME, "rb+");
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

// IZBRISI (21)
void obrisiMeso() {
    FILE* fp = fopen(FILE_NAME, "rb");
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

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (pronaden)
        printf("Obrisano!\n");
    else
        printf("Nije pronadeno!\n");

}
//23 26
int usporediPoCijeni(const void* a, const void* b) {

    Meso* m1 = (Meso*)a;
    Meso* m2 = (Meso*)b;

    if (m1->cijena > m2->cijena) return 1;
    if (m1->cijena < m2->cijena) return -1;
    return 0;
}
//16 17 20 23
void sortirajPoCijeni() {
    FILE* fp = fopen(FILE_NAME, "rb");
    if (!fp) return;

    fseek(fp, 0, SEEK_END);
    int n = ftell(fp) / sizeof(Meso);
    rewind(fp);
    Meso* niz = (Meso*)malloc(n * sizeof(Meso));
    if (niz == NULL) {
        printf("Greska: nema dovoljno memorije");
        fclose(fp);
        return;
    }
    fread(niz, sizeof(Meso), n, fp);
    fclose(fp);
    //23
    qsort(niz, n, sizeof(Meso), usporediPoCijeni);
    printf("\n======SORITRANO PO CIJENI======");

    for (int i = 0; i < n; i++) {
        printf("\n%d | %s | %.2f | %.2f\n", niz[i].id,
            niz[i].naziv,
            niz[i].cijena,
            niz[i].kolicina);
    }
    //18
    free(niz);
    niz = NULL;
}
int cmpPoId(const void* a, const void* b) {
    Meso* m1 = (Meso*)a;
    Meso* m2 = (Meso*)b;

    if (m1->id > m2->id) return 1;
    if (m1->id < m2->id) return -1;
    return 0;
}

void pretraziMeso() {

    FILE* fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        perror("Greska");
        return;
    }

    fseek(fp, 0, SEEK_END);
    int n = ftell(fp) / sizeof(Meso);
    rewind(fp);

    Meso* niz = malloc(n * sizeof(Meso));

    if (!niz) {
        fclose(fp);
        return;
    }

    fread(niz, sizeof(Meso), n, fp);
    fclose(fp);


    qsort(niz, n, sizeof(Meso), cmpPoId);

    int trazeniId;
    printf("Unesi ID: ");
    scanf("%d", &trazeniId);

    Meso kljuc;
    kljuc.id = trazeniId;

    Meso* rezultat = bsearch(
        &kljuc,
        niz,
        n,
        sizeof(Meso),
        cmpPoId
    );

    if (rezultat) {
        printf("\nPRONADENO:\n");
        printf("%d %s %.2f %.2f\n",
            rezultat->id,
            rezultat->naziv,
            rezultat->cijena,
            rezultat->kolicina);
    }
    else {
        printf("Nije pronadeno!\n");
    }

    free(niz);
    niz = NULL;
}
