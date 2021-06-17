#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "routerecords.h"

int fillRecords(RouteRecord* r, FILE* fileIn) {
    
	int i;
	char c;
	int count = 0;
	int numVal = 0;
	char buffer[100];
	
    for (c = getc(fileIn); c != EOF; c = getc(fileIn)) { // gets number of lines to go through
        if (c == '\n')
            count = count + 1; 
    }
        rewind(fileIn);
	
	fgets(buffer, 100, fileIn); // skips first line
	
    for (i = 0; i < (count - 1); i++) {
		
		static int month;
		char org[4];
		char des[4];
		char al[3];
		char pas[12];
		static int numPas;
		
		fscanf(fileIn, "%d,%3s,%3s,%2s,%10s,%d", &month, org, des, al, pas, &numPas);
		
		if (findAirlineRoute(r, count, org, des, al, count) != -1) { // finds if there is already a route with that info, if not makes one
			
		} else {
			
			strcpy(r[numVal].airportCode, org);
			strcpy(r[numVal].destCode, des);
			strcpy(r[numVal].airlineCode, al);
			r[numVal].passengers[month] = numPas;
			
			
			numVal = numVal + 1;
		}
		
		
	}
	
	
	return numVal; // returns number of routes made
}

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx) {
    
    int returnVal = -1;
    
    for (int i = 0; i < length; i++) { // goes through each line to see if there is a duplicate route, returns -1 if there is not, or the number of the route if there is
        
        if ((strcmp(r[i].destCode, destination) == 0) && (strcmp(r[i].airportCode, origin) == 0) && (strcmp(r[i].airlineCode, airline) == 0)) {
            
            returnVal = i;
            
        }
        
   }
    
   return returnVal;
  
  
  
	/*
	int returnVal;

	if (curIdx == -1) {
		returnVal = -1;
		return returnVal;
	} else {
		
		if ((strcmp(r[curIdx].destCode, destination) == 0) && (strcmp(r[curIdx].airportCode, origin) == 0) && (strcmp(r[curIdx].airlineCode, airline) == 0)) {
			
			returnVal = 0;
			return returnVal;
			
		} else {
		
		findAirlineRoute(r, length, origin, destination, airline, (curIdx - 1));
	
		}
	
	}
	
	
	*/
	
}

void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st) {
    
    int passengersArray[7];
    int numMatches = 0;
	
	for (int i = 0; i < 7; i++) { // assigns 0 to each NULL array value
		
		passengersArray[i] = 0;
		
	}
	
	
    switch (st) { // 
        
        case ROUTE: 
        
        
            for (int i = 0; i < length; i++) {
                
                if ((strcmp(r[i].airportCode, key1) == 0) && (strcmp(r[i].destCode, key2) == 0)) {
                    
                    printf("%s (%s-%s) ", r[i].airlineCode, r[i].airportCode, r[i].destCode);
                    numMatches++;
                    
                    for (int j = 0; j < 7; j++) {
						passengersArray[j] += r[i].passengers[j];
					}
					
                }
                
            }
            printf("\n");
            printf("%d matches were found.\n", numMatches);
        
        
            break;
            
        case ORIGIN: 
        
        
            for (int i = 0; i < length; i++) {
                
                if ((strcmp(r[i].airportCode, key1) == 0)) {
                    
                    printf("%s (%s-%s) ", r[i].airlineCode, r[i].airportCode, r[i].destCode);
                    numMatches++;
					
					for (int j = 0; j < 7; j++) {
						passengersArray[j] += r[i].passengers[j];
					}
                    
                    
                }
                
            }
            printf("\n");
            printf("%d matches were found.\n", numMatches);
        
        
            break;
        
        case DESTINATION: 
        
        
            for (int i = 0; i < length; i++) {
                
                if ((strcmp(r[i].destCode, key2) == 0)) {
                    
                    printf("%s (%s-%s) ", r[i].airlineCode, r[i].airportCode, r[i].destCode);
                    numMatches++;
                    
                    for (int j = 0; j < 7; j++) {
						passengersArray[j] += r[i].passengers[j];
					}
                    
                }
                
            }
			
            printf("\n");
            printf("%d matches were found.\n", numMatches);
        
                
            break;
        
        case AIRLINE: 

        
            for (int i = 0; i < length; i++) {
                
                if (strcmp(r[i].airlineCode, key1) == 0) {
                    
                    printf("%s (%s-%s) ", r[i].airlineCode, r[i].airportCode, r[i].destCode);
                    numMatches++;
                    
                    for (int j = 0; j < 7; j++) {
						passengersArray[j] += r[i].passengers[j];
					}
                    
                }
                
            }
            printf("\n");
            printf("%d matches were found.\n", numMatches);
        
            break;
        
        default: 
        
        
        
            break;
        
        
    } 
    
    printf("\n\nStatistics\n");
	int totalPass = (passengersArray[1] + passengersArray[2] + passengersArray[3] + passengersArray[4] + passengersArray[6] + passengersArray[5]);
	
    printf("Total Passengers: %d\n", totalPass); // print all the passengers for the route
    printf("Total Passengers in Month 1: %d\n", passengersArray[1]);
    printf("Total Passengers in Month 2: %d\n", passengersArray[2]);
    printf("Total Passengers in Month 3: %d\n", passengersArray[3]);
    printf("Total Passengers in Month 4: %d\n", passengersArray[4]);
    printf("Total Passengers in Month 5: %d\n", passengersArray[5]);
    printf("Total Passengers in Month 6: %d\n\n", passengersArray[6]);
    
    int avgPassengers = ((totalPass) / 6); // calculate and print average
    printf("Average Passengers per Month: %d\n", avgPassengers);
    
    
    
}

void printMenu() {
    printf( "\n\n######### Airline Route Records Database MENU #########\n" );
printf( "1. Search by Route\n" );
printf( "2. Search by Origin Airport\n" );
printf( "3. Search by Destination Airport\n" );
printf( "4. Search by Airline\n" );
printf( "5. Quit\n" );
printf( "Enter your selection: " );
}

RouteRecord* createRecords(FILE* fileIn) {
    char c;
    int numLines = 0;
	int i;
	int j;
    
     for (c = getc(fileIn); c != EOF; c = getc(fileIn)) { // gets number of lines
		 
        if (c == '\n') {
	
            numLines = numLines + 1;
        }
        
    }
    
	rewind(fileIn);
    RouteRecord routes[numLines - 1]; // rewind, create routes...
	
    
    for (i = 0; i < (numLines - 1); i++) { // assigns 0 to each number of passengers for now
        
        for (j = 0; j < 6; j++) {
        routes[i].passengers[j] = 0;
        
        }
	}
		
		RouteRecord *routePointer = routes;
        return routePointer; // create pointer and returns routes
    
}

