#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CreateTrip();

void ListTrips(); 

void menu(){
    printf("--- BUS TICKET SYSTEM ---\n");
    printf("1. Create New Trip\n"); 
    printf("2. List Trips\n");   
    printf("3. Sell Tickets\n");         
    printf("0. Exit\n");
    printf("Your Choice: ");
    int choice;
    scanf("%d", &choice);
    getchar(); 

    switch(choice){
        case 1:
            CreateTrip();
            menu();
            break;
        case 2:
            ListTrips();
            menu();
            break;
        case 3:
            printf("Sell Tickets function is not implemented yet.\n");
            menu();
            break;
        case 0:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
            menu();
    }
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



int main() {

    printf("Welcome To Bus Ticketing System\n");

    menu();

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



    /*
    
    // Dosyaya kaydetme
    
    */

    FILE *file; 
    file = fopen("trips.dat", "a");

    if(file == NULL){
        printf("Error File doesn't exist!\n");
        return;
    }

    fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%d\n", 
            newTrip.ID, 
            newTrip.Departure, 
            newTrip.Arrival, 
            newTrip.Date, 
            newTrip.DepartureTime, 
            newTrip.BusPlate, 
            newTrip.DriverName, 
            newTrip.Seats);
            
    fclose(file);
    
    


}

void ListTrips(){
    FILE *file = fopen("trips.dat", "r");
    if(file == NULL){
        printf("No trips available.\n");
        return;
    }

    char line[250];
    printf("\n--- Available Trips ---\n");
    while(fgets(line, sizeof(line), file)){
        Trip trip;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d", 
               trip.ID, 
               trip.Departure, 
               trip.Arrival, 
               trip.Date, 
               trip.DepartureTime, 
               trip.BusPlate, 
               trip.DriverName, 
               &trip.Seats);
        
        printf("ID: %s | Route: %s -> %s | Date/Time: %s at %s | Plate: %s | Driver: %s | Seats: %d\n", 
               trip.ID, 
               trip.Departure, 
               trip.Arrival, 
               trip.Date, 
               trip.DepartureTime, 
               trip.BusPlate, 
               trip.DriverName, 
               trip.Seats);
    }
    printf("-----------------------\n");

    fclose(file);
}

