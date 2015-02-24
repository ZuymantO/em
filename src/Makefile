
C = gcc
CC = g++
CFLAGS = `pkg-config --cflags opencv`
CCFLAGS = -W -Wall
INC =
LIBS = `pkg-config --libs opencv`
SRCS = $(shell find . -name "*.cpp")
OBJS = $(SRCS:%.cpp=%.o)
EXE=em
BIN=..
all : $(EXE)
	cp $(EXE) $(BIN)/$(EXE)

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

%.o : %.cpp
	$(CC) $(CFLAGS) $(LIBS) -o $@ -c $<

clean :
	rm -f $(OBJS) $(EXE) *~ #*# *.o *.pch
