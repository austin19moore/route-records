#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "routerecords.h"

int main(int argc, char *argv[]) {

    int userMenuInput = -10;
	int numRecords;
    FILE *inFile;
    
    if (argc == 2) { // ends program if there is not the correct number of command line arguements
        
    } else {
        printf("ERROR: Missing file name and end the program");
        return -1;
    }
    
    
    printf("Opening %s...\n", argv[1]);
   
    inFile = fopen(argv[1], "r");
    
    if (inFile == NULL) { // ends program if file does not open correctly
        printf("ERROR: Could not open file and end the program.");
        return -1;
    }
    	
    		
    		RouteRecord* records = createRecords(inFile); // creates routes
			
    		numRecords = fillRecords(records, inFile); // fills routes with info from the file, returns number of routes and assigns it to numRecords...
    		printf("Unique routes operated by airlines: %d\n", numRecords);
    		
    		fclose(inFile);
    
                while (userMenuInput != 5) {
    
    		printMenu();
    		scanf("%d", &userMenuInput);

    		if (userMenuInput == -10) { // shoots error if non integer is entered
    		    printf("Error: non-integer value entered...\n");
    		}
    		
    		if ((userMenuInput > 5) || (userMenuInput < 1)) {
    		    printf("Invalid Choice.\n");
    		}
    		
			char currOrigin[4] = "";
			 char currDestination[4] = "";
			 char currAL[4] = "";
			
    		switch (userMenuInput) { // menu
    		 
    		 case 1:  // search by route
    		 printf("Enter origin: ");
    		 scanf("%s", currOrigin);
    		 
    		 printf("Enter destination: ");
    		 scanf("%s", currDestination);
    		 
    		 printf("Searching by route...\n");
    		 
    		 searchRecords(records, numRecords, currOrigin, currDestination, ROUTE);
    		    break;
    		    
    		 case 2: // search by origin
    		 printf("Enter origin: ");
    		 scanf("%s", currOrigin);
    		 printf("Searching by origin...\n");
    		 
    		 searchRecords(records, numRecords, currOrigin, currDestination, ORIGIN);
    		    break;
    		    
    		 case 3: // search by destination
    		 printf("Enter destination: ");
    		 scanf("%s", currDestination);
    		 printf("Searching by destination...\n");
    		 
    		 searchRecords(records, numRecords, currOrigin, currDestination, DESTINATION);
    		    break;
    		    
    		 case 4: // search by airline
    		 printf("Enter airline: ");
    		 scanf("%s", currAL);
    		 printf("Searching by airline...\n");
    		 
    		 searchRecords(records, numRecords, currAL, currDestination, AIRLINE);
    		    break;
    		    
    		 case 5: // quit
    		 printf("Good-bye!");
    		    break;
    		    
    		 default:
    		    
    		     break; 
    		    
    		}
    
                    
                }
    
    return 0;
}