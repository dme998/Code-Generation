
CC= g++
RM= rm -vf
CPPFLAGS= -g -Wall -std=c++11 -I.
PROGRAM= statSem
OBJFILES= main.o parser.o scanner.o driveScanner.o 

$(PROGRAM): $(OBJFILES)
	$(CC) -o $(PROGRAM) $(OBJFILES)

main.o: main.cpp token.h ptree.h
	$(CC) $(CPPFLAGS) -c main.cpp

parser.o: parser.cpp parser.h
	$(CC) $(CPPFLAGS) -c parser.cpp

scanner.o: scanner.cpp scanner.h
	$(CC) $(CPPFLAGS) -c scanner.cpp

driveScanner.o: driveScanner.cpp driveScanner.h
	$(CC) $(CPPFLAGS) -c driveScanner.cpp

clean:
	$(RM) $(PROGRAM) $(OBJFILES)
