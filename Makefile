
CC= g++
RM= rm -vf
CPPFLAGS= -g -Wall -std=c++11 -I.
PROGRAM= frontEnd
OBJFILES= main.o parser.o

$(PROGRAM): $(OBJFILES)
	$(CC) -o $(PROGRAM) $(OBJFILES)

main.o: main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

parser.o: parser.cpp parser.h
	$(CC) $(CPPFLAGS) -c parser.cpp

clean:
	$(RM) $(PROGRAM) $(OBJFILES)
