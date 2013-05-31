C=gcc
CC=g++
CFLAGS=-W -Wall
CCFLAGS= -W -Wall
INC=
LIB=
OBJ=
SRC=
EXE=em

#Les regles de construction pour chaque executable
all:
	cd ./src ; make all ; cd ../
 
#Mettre ici toutes les regles de clean pour chaque module
clean:
	cd ./src ; make clean ; cd ../
	rm -rf ./*~ ./#*# *.o 

