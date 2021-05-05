
CC= g++
RM= rm -vf
CPPFLAGS= -g -Wall -std=c++11 -I.
PROGRAM= compfs
OBJFILES= main.o parser.o scanner.o driveScanner.o semantics.o compile.o

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

semantics.o: semantics.cpp semantics.h
	$(CC) $(CPPFLAGS) -c semantics.cpp

compile.o: compile.cpp compile.h
	$(CC) $(CPPFLAGS) -c compile.cpp

clean:
	$(RM) $(PROGRAM) $(OBJFILES)
