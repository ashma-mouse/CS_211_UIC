Project6: Archipelago.o Island.o MyList.o
	g++ Archipelago.o Island.o MyList.o -o Project6

Archipelago.o: Archipelago.cpp Island.h
	g++ -c Archipelago.cpp

Island.o: Island.cpp Island.h
	g++ -c Island.cpp

MyList.o: MyList.cpp MyList.h
	g++ -c MyList.cpp

clean:
	rm *.o Project6

run:
	./Project6
