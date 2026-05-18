#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "meso.h"

enum Izbornik {
    IZLAZ = 0,
    DODAJ = 1,
    ISPISI = 2,
    UREDI = 3,
    OBRISI = 4
};

int main() {

    int izbor;

    do {
        printf("\n===== EVIDENCIJA MESA =====\n");
        printf("1. Dodaj\n");
        printf("2. Ispisi\n");
        printf("3. Uredi\n");
        printf("4. Obrisi\n");
        printf("0. Izlaz\n");

        printf("Odabir: ");
        scanf("%d", &izbor);

        switch (izbor) {

        case DODAJ:
            dodajMeso();
            break;

        case ISPISI:
            ispisiMeso();
            break;

        case UREDI:
            urediMeso();
            break;

        case OBRISI:
            obrisiMeso();
            break;

        case IZLAZ:
            printf("Izlaz\n");
            break;

        default:
            printf("Krivi unos\n");
        }

    } while (izbor != 0);

    return 0;
}