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

typedef struct{
    char TicketID[20];
    char TripId[20];
    char PassengerName[50];
    int SeatNumber;
}Ticket;

void tripMenu();

//trip functions

void CreateTrip();

void ListTrips();

void eraseTrip();

void changeTrip();

int checkID(char * id);

void tripDetails();



int validateTrip(Trip *trip);

//end of trip functions

void ticketMenu();

//ticket functions

void listTickets();

void buyTicket();

void receipt(Ticket ticket, Trip trip);

void cancelTicket();

//end of ticket functions


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

//menu function sum of two menus


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
    
    
        if(!validateTrip(&newTrip)){
                    printf("Invalid trip details entered. Creating operation aborted.\n");
  
                }
        else{
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
                file = fopen("trips.txt", "a");

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

    




}

void ListTrips(){
    FILE *file = fopen("trips.txt", "r");
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
    FILE *file = fopen("trips.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
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

                
                



                /*

                // Dosyaya kaydetme

                */

                if(!validateTrip(&newTrip)){
                    printf("Invalid trip details entered. Update operation aborted.\n");
                    fputs(line,tempFile); // Eski veriyi koru
                }else{

                // Girilen bilgilerin özeti
                printf("\n--- Trip Created Successfully ---\n");
                printf("ID: %s\n", id);
                printf("Route: %s -> %s\n", newTrip.Departure, newTrip.Arrival);
                printf("Date/Time: %s at %s\n", newTrip.Date, newTrip.DepartureTime);
                printf("Plate: %s\n", newTrip.BusPlate);
                printf("Driver: %s\n", newTrip.DriverName);
                printf("Seats: %d\n", newTrip.Seats);
                printf("---------------------------------\n");
                

                fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|%d\n",
                        id,
                        newTrip.Departure,
                        newTrip.Arrival,
                        newTrip.Date,
                        newTrip.DepartureTime,
                        newTrip.BusPlate,
                        newTrip.DriverName,
                        newTrip.Seats);


                }






        }else{
            fputs(line,tempFile);
        }

    }

    if(!found){
        printf("Trip with ID %s not found.\n", id);
    }

    fclose(file);
    fclose(tempFile);

    remove("trips.txt");
    rename("temp.txt","trips.txt");

}

void eraseTrip(){

     // Trip silme fonksiyonu burada implemente edilebilir
    FILE *file = fopen("trips.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
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

    remove("trips.txt");
    rename("temp.txt","trips.txt");

    return;
}

int checkID(char * id){
    FILE *file = fopen("trips.txt", "r");
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
    FILE *file = fopen("trips.txt", "r");
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

int validateTrip(Trip *trip)
{
    
    if(trip->Seats <= 0){
        return 0; // Invalid
    }else if(strlen(trip->ID) == 0 || strlen(trip->Departure) == 0 || strlen(trip->Arrival) == 0 ||
             strlen(trip->Date) == 0 || strlen(trip->DepartureTime) == 0 ||
             strlen(trip->BusPlate) == 0 || strlen(trip->DriverName) == 0){
        return 0; // Invalid
    }
    return 1; // Valid
}


void buyTicket(){
    FILE *tripFile = fopen("trips.txt", "r");
    if(tripFile == NULL){
        printf("No trips available. Cannot buy ticket.\n");
        return;
    }
    FILE *file = fopen("tickets.txt", "a");
    if(file == NULL){
        printf("Error opening ticket file.\n");
        return; 
    }

    Ticket newTicket;
    printf("--- Buy Ticket ---\n");
    
    
    printf("Trip ID: ");
    fgets(newTicket.TripId, sizeof(newTicket.TripId), stdin);
    newTicket.TripId[strcspn(newTicket.TripId, "\n")] = 0;

    // Check if Trip ID exists
    char line[250];
    int tripFound = 0;
    while(fgets(line, sizeof(line), tripFile)){
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

        if(strcmp(trip.ID, newTicket.TripId) == 0){
            tripFound = 1;

            // For simplicity, assign last seat number 

            newTicket.SeatNumber = trip.Seats; // For simplicity, assign last seat number

            sprintf(newTicket.TicketID,"%stbt%d", trip.ID, newTicket.SeatNumber); // Simple Ticket ID generation

            break;
        }
        
    }
    
    fclose(tripFile);

    if(!tripFound){
        printf("Trip with ID %s not found.\n", newTicket.TripId);
        fclose(file);
        return;
    }

    /*
    
    printf("Ticket ID: ");
    fgets(newTicket.TicketID, sizeof(newTicket.TicketID), stdin);
    newTicket.TicketID[strcspn(newTicket.TicketID, "\n")] = 0;
    
    */


    printf("Passenger Name: ");
    fgets(newTicket.PassengerName, sizeof(newTicket.PassengerName), stdin);
    newTicket.PassengerName[strcspn(newTicket.PassengerName, "\n")] = 0;

    // Save ticket to file
    fprintf(file, "%s|%s|%s|%d\n",
            newTicket.TicketID,
            newTicket.TripId,
            newTicket.PassengerName,
            newTicket.SeatNumber);
    
    printf("Ticket purchased successfully! Ticket ID: %s, Trip ID: %s, Passenger: %s, Seat Number: %d\n",
           newTicket.TicketID,
           newTicket.TripId,
           newTicket.PassengerName,
           newTicket.SeatNumber);   
    fclose(file);



    // Update trip seats and create receipt

    char line2[300];

    FILE *tripFileUpdate = fopen("trips.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if(tripFileUpdate == NULL||tempFile == NULL){
        printf("Database corrupted.\n");
        return;
    }

    while (fgets(line2,sizeof(line2),tripFileUpdate))
    {
        Trip trip;
        sscanf(line2, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
               trip.ID,
               trip.Departure,
               trip.Arrival,
               trip.Date,
               trip.DepartureTime,
               trip.BusPlate,
               trip.DriverName,
               &trip.Seats);

        if(strcmp(trip.ID,newTicket.TripId)==0){
            
            trip.Seats -= 1; // Decrease available seats


            //Create receipt

            receipt(newTicket, trip);
        }

        fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|%d\n",
                trip.ID,
                trip.Departure,
                trip.Arrival,
                trip.Date,
                trip.DepartureTime,
                trip.BusPlate,
                trip.DriverName,
                trip.Seats);

    }




    
    fclose(tripFileUpdate);
    fclose(tempFile);

   

    remove("trips.txt");
    rename("temp.txt","trips.txt");


  

}

void cancelTicket(){
    FILE *file = fopen("tickets.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if(file == NULL||tempFile == NULL){
        printf("Database corrupted.\n");
        return;
    }
    char tripID2[20];
    char line[300];
    printf("\n--- Cancel Ticket ---\n");

    char ticketID[20];
    printf("Type Ticket ID to cancel.\n");
    fgets(ticketID, sizeof(ticketID), stdin);
    ticketID[strcspn(ticketID, "\n")] = 0;
    int found = 0;

    while (fgets(line,sizeof(line),file))
    {
        Ticket ticket;

        
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d",
               ticket.TicketID,
               ticket.TripId,
               ticket.PassengerName,
               &ticket.SeatNumber);

        if(strcmp(ticket.TicketID,ticketID)==0){
            found = 1;
            printf("Ticket with ID %s cancelled successfully.\n", ticketID);
            
            //ticket id scope increase
            strcpy(tripID2, ticket.TripId);
        }else{
            fputs(line,tempFile);
        }

    }

    if(!found){
        printf("Ticket with ID %s not found.\n", ticketID);
    }

    fclose(file);
    fclose(tempFile);

    remove("tickets.txt");
    rename("temp.txt","tickets.txt");

    if(found==1){
        // increasing trip seats by one 

        char line2[300];

        FILE *tripFile = fopen("trips.txt", "r");
        FILE *tempFile2 = fopen("temp2.txt", "w");

        if(tripFile == NULL||tempFile2 == NULL){
            printf("Database corrupted.\n");
            return;
        }

        while(fgets(line2,sizeof(line2),tripFile)){

            Trip trip;
            sscanf(line2,"%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
                   trip.ID,
                   trip.Departure,
                   trip.Arrival,
                   trip.Date,
                   trip.DepartureTime,
                   trip.BusPlate,
                   trip.DriverName,
                   &trip.Seats);

            if(strcmp(trip.ID,tripID2)==0){
                trip.Seats += 1; // Increase available seats
            }

            fprintf(tempFile2, "%s|%s|%s|%s|%s|%s|%s|%d\n",
                    trip.ID,
                    trip.Departure,
                    trip.Arrival,
                    trip.Date,
                    trip.DepartureTime,
                    trip.BusPlate,
                    trip.DriverName,
                    trip.Seats);
            


        }
        
        fclose(tripFile);
        fclose(tempFile2);

        remove("trips.txt");
        rename("temp2.txt","trips.txt");



    }
    

}

void listTickets(){
    FILE *file = fopen("tickets.txt", "r");
    if(file == NULL){
        printf("No tickets available.\n");
        return;
    }

    char line[250];
    printf("\n--- Purchased Tickets ---\n");
    while(fgets(line, sizeof(line), file)){
        Ticket ticket;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d",
               ticket.TicketID,
               ticket.TripId,
               ticket.PassengerName,
               &ticket.SeatNumber);

        printf("Ticket ID: %s | Trip ID: %s | Passenger: %s | Seat Number: %d\n",
               ticket.TicketID,
               ticket.TripId,
               ticket.PassengerName,
               ticket.SeatNumber);
    }
    printf("-------------------------\n");

    fclose(file);
}

void receipt(Ticket ticket, Trip trip){
   

    char fileName[50];

    sprintf(fileName, "receipt_%s.txt", ticket.PassengerName);

    FILE *file = fopen(fileName, "w");

    if(file == NULL){
        printf("Error creating receipt file.\n");
        return;
    }

    fprintf(file, "########################################\n");
    fprintf(file, "          BUS TICKET RECEIPT            \n");
    fprintf(file, "########################################\n");
    fprintf(file, "Ticket ID      : %s\n", ticket.TicketID);
    fprintf(file, "Passenger Name : %s\n", ticket.PassengerName);
    fprintf(file, "----------------------------------------\n");
    fprintf(file, "Trip ID        : %s\n", ticket.TripId);
    fprintf(file, "From           : %s\n", trip.Departure);
    fprintf(file, "To             : %s\n", trip.Arrival);
    fprintf(file, "Date           : %s\n", trip.Date);
    fprintf(file, "Time           : %s\n", trip.DepartureTime);
    fprintf(file, "Bus Plate      : %s\n", trip.BusPlate);
    fprintf(file, "Seat Number    : %d\n", ticket.SeatNumber);
    fprintf(file, "########################################\n");
    fprintf(file, "         HAVE A SAFE JOURNEY!           \n");
    fprintf(file, "########################################\n");

    fclose(file);


}

void ticketMenu(){
    while(1){
            printf("--- BUS TİCKET SYSTEM ---\n");
            printf("1. Buy Ticket\n");
            printf("2. Cancel Ticket\n");
            printf("3. List Tickets\n");
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
            case 3:
                listTickets();
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



