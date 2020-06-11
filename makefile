OS: OS.o OS2.o OS3.o
	g++ -o OS OS.o OS2.o OS3.o
OS.o: OS.cpp OS.h OS2.h OS3.h
	g++ -c OS.cpp
OS2.o: OS2.cpp OS.h OS2.h
	g++ -c OS2.cpp
OS3.o: OS3.cpp OS.h OS2.h OS3.h
	g++ -c OS3.cpp
clean:
	rm OS.o OS2.o OS3.o
