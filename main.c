#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void ListTrips();

void eraseTrip();

void changeTrip();

int checkID(char * id);

void tripDetails();

void buyTicket();

void cancelTicket();





void ticketMenu(){
    while(1){
            printf("--- BUS TİCKET SYSTEM ---\n");
            printf("1. Buy Ticket\n");
            printf("2. Cancel Ticket\n");
            printf("0. Exit\n");
            printf("Your Choice: ");

            int choice;

            scanf("%d",&choice);
            getchar();

            switch(choice){
            case 1:
                buyTicket();
                break;
            
            case 2:
                cancelTicket();
                break;
            case 0:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice! Please try again.");

        }


    }
}

void tripMenu(){
    
    while(1){

                printf("--- BUS TRİP SYSTEM ---\n");
                printf("1. Create New Trip\n");
                printf("2. List Trips\n");
                printf("3. Trip Details\n");
                printf("4. Erase Trip\n");
                printf("5. Change Trip Details\n");
                printf("0. Exit\n");
                printf("Your Choice: ");

                int choice;

                scanf("%d", &choice);
                getchar();

                switch(choice){
                    case 1:
                        CreateTrip();
                        break;
                    case 2:
                        ListTrips();
                        break;
                    case 3:
                        tripDetails();
                        break;
                    case 4:
                        eraseTrip();
                        break;
                    case 5:
                        changeTrip();
                        break;
                    case 0:
                        printf("Exiting...\n");
                        return;
                    default:
                        printf("Invalid choice! Please try again.\n");

                    }
                }

}



void menu(){

    int choice;
    while(1){
        printf("--- MAIN MENU ---\n");
        printf("1. Trip Management\n");
        printf("2. Ticket Management\n");
        printf("0. Exit\n");
        printf("Your Choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1:
                tripMenu();
                break;
            case 2:
                ticketMenu();
                break;
            case 0:
                printf("Exiting...\n");
                exit(0);
            default :
                printf("Invalid choice! Please try again.\n");
        }
    }
}


/*

Firstly i try recrusive function for menu but it is not efficient. İt may cause stack overflow.

*/




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

    if(checkID(newTrip.ID)){
        printf("Trip creation aborted due to duplicate ID.\n");
        return;
    }

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


    // Checking number of seats is greater than zero because we cant define negative values as number of seats.

    do{
        printf("Number of Seats:");
        scanf("%d", &newTrip.Seats);
        getchar();
        printf("\n");
        if(newTrip.Seats <= 0){
            printf("-> Number of seats must be greater than zero!\n");
        }
    }while(newTrip.Seats <= 0);
    
    

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

void changeTrip(){
    // Trip silme fonksiyonu burada implemente edilebilir
    FILE *file = fopen("trips.dat", "r");
    FILE *tempFile = fopen("temp.dat", "w");
    if(file == NULL||tempFile == NULL){
        printf("Database corrupted.\n");
        return;
    }

    char line[300];
    printf("\n--- Change Trip Details ---\n");
    printf("Enter Trip ID to change: ");
    char id[20];
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;
    int found = 0;

    while (fgets(line,sizeof(line),file))
    {
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

        if(strcmp(trip.ID,id)==0){
            found = 1;
            printf("Trip with ID %s found. Enter new details.\n", id);
            // Yeni detayları al

                Trip newTrip;

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

                do{
                    printf("Number of Seats:");
                    scanf("%d", &newTrip.Seats);
                    getchar();
                    printf("\n");
                    if(newTrip.Seats <= 0){
                        printf("-> Number of seats must be greater than zero!\n");
                    }
                }while(newTrip.Seats <= 0);
    

                // Girilen bilgilerin özeti
                printf("\n--- Trip Created Successfully ---\n");
                printf("ID: %s\n", id);
                printf("Route: %s -> %s\n", newTrip.Departure, newTrip.Arrival);
                printf("Date/Time: %s at %s\n", newTrip.Date, newTrip.DepartureTime);
                printf("Plate: %s\n", newTrip.BusPlate);
                printf("Driver: %s\n", newTrip.DriverName);
                printf("Seats: %d\n", newTrip.Seats);
                printf("---------------------------------\n");



                /*

                // Dosyaya kaydetme

                */



                fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|%d\n",
                        id,
                        newTrip.Departure,
                        newTrip.Arrival,
                        newTrip.Date,
                        newTrip.DepartureTime,
                        newTrip.BusPlate,
                        newTrip.DriverName,
                        newTrip.Seats);









        }else{
            fputs(line,tempFile);
        }

    }

    if(!found){
        printf("Trip with ID %s not found.\n", id);
    }

    fclose(file);
    fclose(tempFile);

    remove("trips.dat");
    rename("temp.dat","trips.dat");

}

void eraseTrip(){

     // Trip silme fonksiyonu burada implemente edilebilir
    FILE *file = fopen("trips.dat", "r");
    FILE *tempFile = fopen("temp.dat", "w");
    if(file == NULL||tempFile == NULL){
        printf("Database corrupted.\n");
        return;
    }

    char line[300];
    printf("\n--- Erase Trip ---\n");

    char id[20];
    printf("Type Trip ID to erase.\n");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;
    int found = 0;

    while (fgets(line,sizeof(line),file))
    {
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

        if(strcmp(trip.ID,id)==0){
            found = 1;
            printf("Trip with ID %s erased successfully.\n", id);
        }else{
            fputs(line,tempFile);
        }

    }

    if(!found){
        printf("Trip with ID %s not found.\n", id);
    }

    fclose(file);
    fclose(tempFile);

    remove("trips.dat");
    rename("temp.dat","trips.dat");

    return;
}

int checkID(char * id){
    FILE *file = fopen("trips.dat", "r");
    if(file == NULL){
        printf("No trips available.\n");
        return 0;
    }

    char line[250];
    char tempID[20];

    while(fgets(line, sizeof(line), file)){

        sscanf(line, "%[^|]|", tempID);

        if(strcmp(tempID, id) == 0){
            printf("-> This ID already exists!\n");
            fclose(file);
            return 1;
        }
    }


    fclose(file);
    return 0;
}

void tripDetails(){
    FILE *file = fopen("trips.dat", "r");
    if(file == NULL){
        printf("No trips available.\n");
        return;
    }

    char id[20];
    printf("Enter Trip ID to view details: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    char line[250];
    int found = 0;

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

        if(strcmp(trip.ID, id) == 0){
            found = 1;
            printf("\n--- Trip Details ---\n");
            printf("ID: %s\n", trip.ID);
            printf("Route: %s -> %s\n", trip.Departure, trip.Arrival);
            printf("Date/Time: %s at %s\n", trip.Date, trip.DepartureTime);
            printf("Plate: %s\n", trip.BusPlate);
            printf("Driver: %s\n", trip.DriverName);
            printf("Seats: %d\n", trip.Seats);
            printf("---------------------\n");
            break;
        }
    }

    if(!found){
        printf("Trip with ID %s not found.\n", id);
    }

    fclose(file);
}

void buyTicket(){
    printf("Buy Ticket function is not implemented yet.\n");
}
void cancelTicket(){
    printf("Cancel Ticket function is not implemented yet.\n");
}