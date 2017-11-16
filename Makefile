COMPILER = g++
FLAGS = -std=c++11 -Wall -g
EXECUTABLE = cache-sim


all: Project2.o DirectMapped.o SetAssociative.o FullyAssociative.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE) Project2.o DirectMapped.o SetAssociative.o FullyAssociative.o

Project2.o: Project2.cpp
	$(COMPILER) $(FLAGS) -c Project2.cpp

DirectMapped.o: DirectMapped.cpp
	$(COMPILER) $(FLAGS) -c DirectMapped.cpp

SetAssociative.o: SetAssociative.cpp
	$(COMPILER) $(FLAGS) -c SetAssociative.cpp

FullyAssociative.o: FullyAssociative.cpp
	$(COMPILER) $(FLAGS) -c FullyAssociative.cpp

clean:
	rm -rf *.o $(EXECUTABLE) $(EXECUTABLE).dSYM output.txt