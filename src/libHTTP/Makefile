# Makefile for lib http

PROFILE = Debug
CC = gcc
OUTDIR = output/$(PROFILE)
OBJDIR = obj/$(PROFILE)
SRCDIR = cpp
DEPS = libBase

TARGET = $(OUTDIR)/libHTTP.a
OBJECTS = $(OBJDIR)/libhttp.o $(OBJDIR)/libsocket.o
SRCS = $(SRCDIR)/libhttp.cpp $(SRCDIR)/libsocket.cpp
INCLUDE = ../$(DEPS)/header
# OPTS = -O2
OPTS = -g
CFLAGS = -W -Wall  -I $(INCLUDE) $(OPTS)
LDFLAGS = 
LDLIBS = 

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

objs/libhttp.o : cpp/libhttp.cpp
	$(CC) $(CFLAGS) -c -o objs/libhttp.o cpp/libhttp.cpp

objs/libsocket.o : cpp/libsocket.cpp
	$(CC) $(CFLAGS) -c -o objs/libsocket.o cpp/libsocket.cpp

clean:
	rm -f $(OUTDIR)/*.a
	rm -f $(OBJDIR)/*.o

