#Flags for compiler
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g

#Directories where compiler can find things
INCLUDE = -Iinclude
BINDIR = ./bin/
SRCDIR = ./src/
OBJDIR = ./obj/

PROGNAME = program
TESTHASH = testHash

all: assignment testHashTable

assignment: main.o dictFunc.o hashT.o fileIO.o
	$(CC) $(OBJDIR)hashT.o $(OBJDIR)fileIO.o $(OBJDIR)dictFunc.o $(OBJDIR)main.o -o $(BINDIR)$(PROGNAME)

testHashTable: testHash.o hashT.o
	$(CC) $(OBJDIR)hashT.o $(OBJDIR)testHash.o -o $(BINDIR)$(TESTHASH)
main.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)main.c -o $(OBJDIR)main.o

dictFunc.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)DictionaryFunctions.c -o $(OBJDIR)dictFunc.o

hashT.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)HashTableAPI.c -o $(OBJDIR)hashT.o

testHash.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)testHashTableAPI.c -o $(OBJDIR)testHash.o

fileIO.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)FileIO.c -o $(OBJDIR)fileIO.o

clean:
	rm $(OBJDIR)*.o $(BINDIR)$(PROGNAME) $(BINDIR)$(TESTHASH)
