
CC= g++
RM= rm -vf
CPPFLAGS= -g -Wall -std=c++11 -I.
PROGRAM= frontEnd
OBJFILES= main.o parser.o scanner.o testScanner.o 

$(PROGRAM): $(OBJFILES)
	$(CC) -o $(PROGRAM) $(OBJFILES)

main.o: main.cpp token.h node.h
	$(CC) $(CPPFLAGS) -c main.cpp

parser.o: parser.cpp parser.h
	$(CC) $(CPPFLAGS) -c parser.cpp

scanner.o: scanner.cpp scanner.h
	$(CC) $(CPPFLAGS) -c scanner.cpp

testScanner.o: testScanner.cpp testScanner.h
	$(CC) $(CPPFLAGS) -c testScanner.cpp

clean:
	$(RM) $(PROGRAM) $(OBJFILES)
