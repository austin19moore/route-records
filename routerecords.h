#ifndef ROUTERECORDS
#define ROUTERECORDS

typedef enum SearchType { ROUTE, ORIGIN, DESTINATION, AIRLINE } SearchType;

typedef struct RouteRecord_struct {
    
    char airportCode[4];
    char destCode[4];
    char airlineCode[3];
    int passengers[7];
    
} RouteRecord;

void printMenu();

int fillRecords(RouteRecord* r, FILE* fileIn);

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);

void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st);

RouteRecord* createRecords(FILE* fileIn);

#endif