#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meso.h"
#include "globals.h"

void dodajMeso() {
    FILE* fp = fopen(FILE_NAME, "ab");
    if (!fp) return;

    Meso m;

    printf("ID: ");
    if (scanf("%d", &m.id) != 1) { fclose(fp); return; }

    if (m.id <= 0) {
        printf("Neispravan ID!\n");
        fclose(fp);
        return;
    }

    printf("Naziv: ");
    scanf("%49s", m.naziv);

    printf("Cijena: ");
    if (scanf("%f", &m.cijena) != 1) { fclose(fp); return; }

    if (m.cijena <= 0) {
        printf("Neispravna cijena!\n");
        fclose(fp);
        return;
    }

    printf("Kolicina: ");
    if (scanf("%f", &m.kolicina) != 1) { fclose(fp); return; }

    if (m.kolicina <= 0) {
        printf("Kolicina neispravna!\n");
        fclose(fp);
        return;
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

    ispisiNaslov();
    ispisiRekurzivno(fp);

    fclose(fp);
}

    void ispisiRekurzivno(FILE* fp) {

    Meso m;

    if (fread(&m, sizeof(Meso), 1, fp) != 1)
        return;

    printf("\n%d | %s | %.2f | %.2f | %.2f",
        m.id,
        m.naziv,
        m.cijena,
        m.kolicina,
        vrijednost(m));

    ispisiRekurzivno(fp);
}

void urediMeso() {
    FILE* fp = fopen(FILE_NAME, "rb+");
    if (!fp) return;

    int id;
    int pronaden = 0;
    Meso m;

    printf("ID za urediti: ");
    if (scanf("%d", &id) != 1) { fclose(fp); return; }

    while (fread(&m, sizeof(Meso), 1, fp) == 1) {
        if (m.id == id) {
            printf("Novi naziv: ");
            scanf("%49s", m.naziv);

            printf("Nova cijena: ");
            if (scanf("%f", &m.cijena) != 1) break;

            printf("Nova kolicina: ");
            if (scanf("%f", &m.kolicina) != 1) break;

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

void obrisiMeso() {
    FILE* fp = fopen(FILE_NAME, "rb");
    FILE* temp = fopen("temp.dat", "wb");

    if (!fp || !temp) {
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    int id;
    int pronaden = 0;
    Meso m;

    printf("ID za brisanje: ");
    if (scanf("%d", &id) != 1) { fclose(fp); fclose(temp); return; }

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

int usporediPoCijeni(const void* a, const void* b) {

    const Meso* m1 = (const Meso*)a;
    const Meso* m2 = (const Meso*)b;

    if (m1->cijena > m2->cijena) return 1;
    if (m1->cijena < m2->cijena) return -1;
    return 0;
}

void sortirajPoCijeni() {
    FILE* fp = fopen(FILE_NAME, "rb");
    if (!fp) return;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    int n = (int)(size / sizeof(Meso));
    rewind(fp);
    if (n == 0) {
        printf("Nema podataka.\n");
        fclose(fp);
        return;
    }
    Meso* niz = (Meso*)malloc(n * sizeof(Meso));
    if (niz == NULL) {
        printf("Greska: nema dovoljno memorije");
        fclose(fp);
        return;
    }
    if (fread(niz, sizeof(Meso), n, fp) != (size_t)n) {
        printf("Greska pri citanju datoteke.\n");
        free(niz);
        fclose(fp);
        return;
    }
    fclose(fp);
    qsort(niz, n, sizeof(Meso), usporediPoCijeni);
    printf("\n======SORTEIRANO PO CIJENI======");

    for (int i = 0; i < n; i++) {
        printf("\n%d | %s | %.2f | %.2f | %.2f",
            niz[i].id,
            niz[i].naziv,
            niz[i].cijena,
            niz[i].kolicina,
            vrijednost(niz[i]));
    }

    free(niz);
    niz = NULL;
}

int cmpPoId(const void* a, const void* b) {
    const Meso* m1 = (const Meso*)a;
    const Meso* m2 = (const Meso*)b;

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
    long size = ftell(fp);
    int n = (int)(size / sizeof(Meso));
    rewind(fp);
    if (n == 0) {
        printf("Nema podataka.\n");
        fclose(fp);
        return;
    }

    Meso* niz = malloc(n * sizeof(Meso));

    if (!niz) {
        fclose(fp);
        return;
    }

    if (fread(niz, sizeof(Meso), n, fp) != (size_t)n) {
        printf("Greska pri citanju datoteke.\n");
        free(niz);
        fclose(fp);
        return;
    }
    fclose(fp);

    qsort(niz, n, sizeof(Meso), cmpPoId);

    int trazeniId;
    printf("Unesi ID: ");
    if (scanf("%d", &trazeniId) != 1) { free(niz); return; }

    Meso kljuc;
    memset(&kljuc, 0, sizeof(Meso));
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
