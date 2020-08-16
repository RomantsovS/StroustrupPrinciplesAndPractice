all: drill.exe

drill.exe: drill.o
	 g++ -o drill.exe drill.o

drill.o: drill.cpp
	 g++ -c drill.cpp
     
clean:
	 rm *.o drill.exe
