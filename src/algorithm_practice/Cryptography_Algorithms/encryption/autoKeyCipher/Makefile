#
# This is an example Makefile for a caesar cipher program.  This
# program uses both the caesar cipher module and a crypto analysis module.
# Typing 'make' or 'make main' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    			adds debugging information to the executable file
#  -Wall 			turns on most, but not all, compiler warnings
#  -std=c++11	turns on c++11 options
#
# for C++ define  CC = g++
CC=g++
CFLAGS=-O3 -std=c++11 -Wall

all: main

main: autoKey.o
	$(CC) $(CFLAGS) autoKey.o main.cpp -o main

autoKey.o: autoKey.cpp autoKey.h
	$(CC) $(CFLAGS) -c autoKey.cpp

# cryptoAnalysis.o: cryptoAnalysis.h cryptoAnalysis.cpp \
# 									caesarCipher.h caesarCipher.cpp
# 	$(CC) $(CFLAGS) -c cryptoAnalysis.cpp caesarCipher.cpp
#
# caesarCipher.o: caesarCipher.h caesarCipher.cpp
# 	$(CC) $(CFLAGS) -c caesarCipher.cpp
#
clean:
	rm *.o main
