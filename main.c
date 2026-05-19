#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "meso.h"
//10 11
enum Izbornik {
    IZLAZ = 0,
    DODAJ = 1,
    ISPISI = 2,
    UREDI = 3,
    OBRISI = 4,
    SORTIRAJ = 5
    
};
//7
int main() {

    int izbor;
    //10
    do {
        printf("\n===== EVIDENCIJA MESA =====\n");
        printf("1. Dodaj\n");
        printf("2. Ispisi\n");
        printf("3. Uredi\n");
        printf("4. Obrisi\n");
        printf("5. Sortiraj po cijeni\n");
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

        case SORTIRAJ:
            sortirajPoCijeni();
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
