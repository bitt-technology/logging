

SRC = logging.c test.c
HDR = logging.h
OBJ = logging.o test.o
EXE = test


all: $(EXE)

$(EXE): $(OBJ) 
	gcc -Wall -ansi -pedantic -O3 -o test $(OBJ)


$(OBJ): $(HDR) $(SRC)
	gcc -c --std=c99 $(SRC)

clean:
	rm -rf $(OBJ)
	rm -rf $(EXE)




