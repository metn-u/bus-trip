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
    char ID[20];
    char Departure[40];
    char Arrival[40];
    char Date[30];
    char DepartureTime[30];
    char BusPlate[30];
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
    fgets(newTrip.ID, sizeof(newTrip.ID),stdin);
    newTrip.ID[strcspn(newTrip.ID, "\n")] = 0;
    printf("\n");

    printf("Departure Point:");
    fgets(newTrip.Departure, sizeof(newTrip.Departure),stdin);
    newTrip.Departure[strcspn(newTrip.Departure, "\n")] = 0;

    printf("\n");
    printf("Arrival Point:");
    fgets(newTrip.Arrival, sizeof(newTrip.Arrival),stdin);
    newTrip.Arrival[strcspn(newTrip.Arrival, "\n")] = 0;
    printf("\n");

    printf("Trip Date:");
    fgets(newTrip.Date, sizeof(newTrip.Date),stdin);
    newTrip.Date[strcspn(newTrip.Date, "\n")] = 0;
    printf("\n");

    printf("Trip departure time:");
    fgets(newTrip.DepartureTime, sizeof(newTrip.DepartureTime),stdin);
    newTrip.DepartureTime[strcspn(newTrip.DepartureTime, "\n")] = 0;
    printf("\n");

    printf("Bus Plate:");
    fgets(newTrip.BusPlate, sizeof(newTrip.BusPlate),stdin);
    newTrip.BusPlate[strcspn(newTrip.BusPlate, "\n")] = 0;
    printf("\n");

    printf("Driver Name:");
    fgets(newTrip.DriverName, sizeof(newTrip.DriverName),stdin);
    newTrip.DriverName[strcspn(newTrip.DriverName, "\n")] = 0;
    printf("\n");

    printf("Number of Seats:");
    scanf("%d", &newTrip.Seats);
    getchar();
    printf("\n");

    // Girilen bilgilerin özeti
    printf("\n--- Trip Created Successfully ---\n");
    printf("ID: %s\n", newTrip.ID);
    printf("Route: %s -> %s\n", newTrip.Departure, newTrip.Arrival);
    printf("Date/Time: %s at %s\n", newTrip.Date, newTrip.DepartureTime);
    printf("Plate: %s\n", newTrip.BusPlate);
    printf("Driver: %s\n", newTrip.DriverName);
    printf("Seats: %d\n", newTrip.Seats);
    printf("---------------------------------\n");




}


