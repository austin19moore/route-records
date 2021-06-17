output: main.o route-records.o
	g++ main.o route-records.o -o output

main.o: main.c
	g++ -c main.c
	
route-records.o: route-records.c routerecords.h
	g++ -c route-records.c

clean: 
	rm *.o output