# Compiler
CC = g++

# object file directory
ODIR = obj

# .o dependancies
_OBJ = $(ODIR)/crng.o $(ODIR)/jrng.o $(ODIR)/EasyBMP.o

all: crng

crng: $(_OBJ)
	$(CC) -g -o $@ $^

$(ODIR)/%.o: %.cpp
	$(CC) -g -c -o $@ $^ -Wall

$(ODIR)/EasyBMP.o: EasyBMP_1.06/EasyBMP.cpp
	$(CC) -g -c -o $@ $^

clean:
	rm $(ODIR)/*.o crng graph.bmp
