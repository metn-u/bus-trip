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
    char Departure[20];
    char Arrival[20];
    char Date[10];
    char DepartureTime[10];
    char BusPlate[10];
    char DriverName[30];
    int Seats;
}Trip;

void CreateTrip();

int main() {

    printf("Welcome To Bus Ticketing System\n");

    CreateTrip();

    return 0;
}

void CreateTrip(){
    Trip newTrip; 

    printf("--- Creating New Trip ---\n");
    printf("Trip ID:");
    scanf("%d", &newTrip.ID);
    printf("\n");

    printf("Departure Point:");
    scanf("%s", newTrip.Departure);
    printf("\n");

    printf("Arrival Point:");
    scanf("%s", newTrip.Arrival);
    printf("\n");

    printf("Trip Date:");
    fgets(newTrip.Date, sizeof(newTrip.Date),stdin);
    printf("\n");

    printf("Trip departure time:");
    fgets(newTrip.DepartureTime, sizeof(newTrip.DepartureTime),stdin);
    printf("\n");

    printf("Bus Plate:");
    fgets(newTrip.BusPlate, sizeof(newTrip.BusPlate),stdin);
    printf("\n");

    printf("Driver Name:");
    fgets(newTrip.DriverName, sizeof(newTrip.DriverName),stdin);
    printf("\n");

    printf("Number of Seats:");
    scanf("%d", &newTrip.Seats);
    printf("\n");

    // Girilen bilgilerin özeti
    printf("\n--- Trip Created Successfully ---\n");
    printf("ID: %d\n", newTrip.ID);
    printf("Route: %s -> %s\n", newTrip.Departure, newTrip.Arrival);
    printf("Date/Time: %s at %s\n", newTrip.Date, newTrip.DepartureTime);
    printf("Plate: %s\n", newTrip.BusPlate);
    printf("Driver: %s\n", newTrip.DriverName);
    printf("Seats: %d\n", newTrip.Seats);
    printf("---------------------------------\n");




}


