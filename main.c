#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void menu(){
    printf("--- OTÖBÜS BİLET SİSTEMİ ---\n");
    printf("1. Yeni Sefer Oluştur\n"); // [cite: 13]
    printf("2. Seferleri Listele\n");   // [cite: 17]
    printf("3. Bilet Satış\n");         // [cite: 18]
    printf("0. Çıkış\n");
    printf("Seçiminiz: ");


}

typedef struct{
    int ID;
    char[] Departure;
    char[] Arrival;
    char[] Date;
    char[] DepartureTime;
    char[] BusPlate;
    char[] DriverName;
    int Seats;
}Trip;



int main() {

    printf("Welcome To Bus Ticketing System\n");

    menu();

    return 0;
}
