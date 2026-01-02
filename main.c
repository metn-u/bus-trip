#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ticket AND Trip Structures

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


//FUNCTIONS PROTOTYPES

//menu functions prototypes

void tripMenu();
void ticketMenu();
void menu();


//trip functions prototypes

void CreateTrip();

void ListTrips();

void eraseTrip();

void changeTrip();

int checkID(char * id);

void tripDetails();


int validateTrip(Trip *trip);

//end of trip functions prototypes 




//ticket functions prototypes

void listTickets();

void buyTicket();

void receipt(Ticket ticket, Trip trip);

void cancelTicket();

//end of ticket functions prototypes


//main function

int main() {

    printf("Welcome To Bus Ticketing System\n");

    menu();

    return 0;



}

//this functions sum of trip and ticket menu functions

void menu(){

    int choice;
    while(1){
        printf("--- MAIN MENU ---\n");
        printf("1. Trip Management\n");
        printf("2. Ticket Management\n");
        printf("0. Exit\n");
        printf("Your Choice: ");
        scanf("%d", &choice);
        getchar(); // Clearing buffer to be sure not skip any things 

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


//Firstly i try recrusive function for menu but it is not efficient. I learned that it could cause stack overflow.


void CreateTrip(){
    Trip newTrip;

    printf("--- Creating New Trip ---\n");
    printf("Trip ID:");
    fgets(newTrip.ID, sizeof(newTrip.ID),stdin);  //taking trip id from user ( giving them chance to assignt their own id)
    newTrip.ID[strcspn(newTrip.ID, "\n")] = 0; // Removing newline character and change it with null "\0"

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
        getchar();                      // clearing buffer to take care 
        printf("\n");
        if(newTrip.Seats <= 0){
            printf("-> Number of seats must be greater than zero!\n");
        }
    }while(newTrip.Seats <= 0);
    
    
        // BE SURE there is no space character for inputs. it may be cause problems to show date in program.

        if(!validateTrip(&newTrip)){
                    printf("Invalid trip details entered. Creating operation aborted.\n");
  
                }
        else{

            // Showing statistic of created trip in CLI
                printf("\n--- Trip Created Successfully ---\n");
                printf("ID: %s\n", newTrip.ID);
                printf("Route: %s -> %s\n", newTrip.Departure, newTrip.Arrival);
                printf("Date/Time: %s at %s\n", newTrip.Date, newTrip.DepartureTime);
                printf("Plate: %s\n", newTrip.BusPlate);
                printf("Driver: %s\n", newTrip.DriverName);
                printf("Seats: %d\n", newTrip.Seats);
                printf("---------------------------------\n");

               
            // Saving trip to file with validated inputs to trips file

                FILE *file;
                file = fopen("trips.txt", "a");

                if(file == NULL){
                    printf("Where did trips data base gone!?\n");
                    return;
                }

                fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%d\n",   // using "|" character to creating database formatted and using this character as splitter in later
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

    char line[250];   //to taking database as variable and use in my program

    printf("\n--- Available Trips ---\n");
    while(fgets(line, sizeof(line), file)){  //Reading trips line by line in trips file
        Trip trip;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",    //taking inputs formatted by using "|" character , split it and assign to trip structure
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
    //Creating temp file and re-write trips datas and manipulates it as i want
    FILE *file = fopen("trips.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if(file == NULL||tempFile == NULL){
        printf("Database corrupted.\n");
        return;
    }

    char line[300];  
    char id[20];

    printf("\n--- Change Trip Details ---\n");
    printf("Enter Trip ID to change: ");
    
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;   // to compare given id and trips id's I change newline to null terminator
    int found = 0; // to check is there trip existed

    while (fgets(line,sizeof(line),file))   //line by line checking loop
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

        if(strcmp(trip.ID,id)==0){   // comparing id and trips id's
            found = 1;
            printf("Trip with ID %s found. Enter new details.\n", id);
                // taking new details

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

                do{         //checking number of seat count 
                    printf("Number of Seats:");
                    scanf("%d", &newTrip.Seats);
                    getchar();
                    printf("\n");
                    if(newTrip.Seats <= 0){
                        printf("-> Number of seats must be greater than zero!\n");
                    }
                }while(newTrip.Seats <= 0);

                
            //saving to file 

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

    // if trips couldnt find 
    if(!found){
        printf("Trip with ID %s not found.\n", id);
    }

    fclose(file);
    fclose(tempFile);

    //removing old unwanted data file and rename updated data file
    remove("trips.txt");
    rename("temp.txt","trips.txt");

}

void eraseTrip(){
    //creating temp file to manıpulate data file
    FILE *file = fopen("trips.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if(file == NULL||tempFile == NULL){
        printf("Database corrupted.\n");
        return;
    }

    char line[300];     //taking trips datas as variable to use in program
    printf("\n--- Erase Trip ---\n");

    char id[20];
    printf("Type Trip ID to erase.\n");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;       // to compare strings easily
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
            fputs(line,tempFile);  //if its not trip it write to temp data file
        }

    }

    if(!found){
        printf("Trip with ID %s not found.\n", id);
    }

    fclose(file);
    fclose(tempFile);


    //removing old trip data file and rename our upgraded data file
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

        sscanf(line, "%[^|]|", tempID);  //just looking for ID variable of structure

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
    int found = 0;  //to check existence of trip 

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
        return 0; // unwanted inputs
    }else if(strlen(trip->ID) == 0 || strlen(trip->Departure) == 0 || strlen(trip->Arrival) == 0 ||
             strlen(trip->Date) == 0 || strlen(trip->DepartureTime) == 0 ||
             strlen(trip->BusPlate) == 0 || strlen(trip->DriverName) == 0){
        return 0; // unwanted input
    }
    return 1; // we can use this inputs
}


void buyTicket(){
    FILE *tripFile = fopen("trips.txt", "r");
    if(tripFile == NULL){
        printf("No trips available. Can't buy ticket.\n");
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

    // checking trips available
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

        if(strcmp(trip.ID, newTicket.TripId) == 0&&trip.Seats>0){
            tripFound = 1;

            // For simplicity, assiging last number

            newTicket.SeatNumber = trip.Seats; // For simplicity, assign last seat number

            sprintf(newTicket.TicketID,"%stbt%d", trip.ID, newTicket.SeatNumber); // Simple Ticket ID generator 

            break;
        }
        
    }
    
    fclose(tripFile);

    if(!tripFound){
        printf("Available trip with ID %s not found.\n", newTicket.TripId);
        fclose(file);
        return;
    }

    /*
    
    printf("Ticket ID: ");
    fgets(newTicket.TicketID, sizeof(newTicket.TicketID), stdin);
    newTicket.TicketID[strcspn(newTicket.TicketID, "\n")] = 0;
    
    */


    //just needed 1 information to buy ticket and other ones created by script made by using sprintf function 

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



    // Updating trip seats and creating receipt

    char line2[300];    //to read lines in data files

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
            
            trip.Seats -= 1; // Decreasing available seats

            //Creating receipt by using receipt function

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

   
    //updating data files as we want
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
    printf("Type Ticket ID to cancel : ");
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

    // saving data files as our wants
    remove("tickets.txt");
    rename("temp.txt","tickets.txt");


    // increasing available seats and rewrite
    if(found==1){

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
   
    // 
    char fileName[50];

    sprintf(fileName, "receipt_%s_%s.txt", ticket.PassengerName,ticket.TicketID);  // receipt name generator to specify receipt for person

    FILE *file = fopen(fileName, "w");

    if(file == NULL){
        printf("Error creating receipt file.\n");
        return;
    }

    fprintf(file, "########################################\n");
    fprintf(file, "          BUS TICKET RECEIPT            \n");
    fprintf(file, "########################################\n");
    fprintf(file, "Ticket ID      : %s\n", ticket.TicketID);
    fprintf(file, "Passenger Name : %s\n", ticket.PassengerName);     //    =================
    fprintf(file, "----------------------------------------\n");      //     receipt format
    fprintf(file, "Trip ID        : %s\n", ticket.TripId);            //    =================
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
            //simple menu system with switch-case
            printf("--- BUS TİCKET SYSTEM ---\n");
            printf("1. Buy Ticket\n");
            printf("2. Cancel Ticket\n");
            printf("3. List Tickets\n");
            printf("0. Exit\n");
            printf("Your Choice: ");

            int choice;

            scanf("%d",&choice);
            getchar();              //to avoid unwanted process

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
                //simple menu system with switch-case
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
                getchar();          //to avoid unwanted process

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



