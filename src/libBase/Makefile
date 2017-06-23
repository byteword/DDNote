# Makefile for lib http

CC = gcc
CFLAGS = -W -Wall
TARGET = libBase.a
OBJECTS = 
HEADERS = oscheck.h


all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(HEADERS) :
	cd header; cp -f $(HEADERS) ../../headers/

clean:
	rm *.o $(TARGET)


