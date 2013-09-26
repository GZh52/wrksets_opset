# Makefile for wrksets
# 
#

CC = gcc
CCFLAGS = -pedantic -Wall -g -DMY_DEBUG
PROGRAM_NAME = wrksets

$(PROGRAM_NAME): main.o \
                 idxfunc.o \
                 printfnc.o \
                 operfunc.o
	$(CC) main.o idxfunc.o printfnc.o operfunc.o -o $(PROGRAM_NAME) -Wall

printfnc.o: printfnc.c \
           elemdata.h \
           printfnc.h
	$(CC) -c printfnc.c $(CCFLAGS)

operfunc.o: operfunc.c \
           elemdata.h \
           printfnc.h \
           operfunc.h
	$(CC) -c operfunc.c $(CCFLAGS)

idxfunc.o: idxfunc.c \
           elemdata.h \
           idxfunc.h
	$(CC) -c idxfunc.c $(CCFLAGS)

main.o: main.c \
        elemdata.h \
        idxfunc.h \
        printfnc.h \
        operfunc.h
	$(CC) -c main.c $(CCFLAGS)

clean:
	rm -f *.o

install:
#

uninstall: 
	rm $(PROGRAM_NAME)
