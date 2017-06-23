# Makefile for lib http

CC = gcc
CFLAGS = -W -Wall
TARGET = libHTTP.a
OBJECTS = libhttp.o libsocket.o
HEADERS = libHTTP.h libSocket.h


all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

libhttp.o : cpp/libhttp.cpp
	$(CC) $(CFLAGS) -c -o libhttp.o libhttp.cpp

libsocket.o : cpp/libsocket.cpp
	$(CC) $(CFLAGS) -c -o libsocket.o libsocket.cpp

$(HEADERS) :
	cd header; cp -f $(HEADERS) ../../headers/

clean:
	rm *.o $(TARGET)


