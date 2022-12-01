# The template for this makefile which has been adapted has been taken from the sample one provided in COMP20003 in W2.5

# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g -ggdb
# Define libraries to be linked (for example -lm)
LDLIBS = 

# Define sets of source files and object files
SRC = dict1.c linkedlists.c
SRC2 = dict2.c linkedlists.c 
# OBJ is the same as SRC, just replace .c with .o

OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)
 
# Define the executable name(s)
EXE = dict1
EXE2 = dict2

# The first target:
$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LDLIBS)

$(EXE2): $(OBJ2) 
	$(CC) $(CFLAGS) -o $(EXE2) $(OBJ2) $(LDLIBS)

clean:
	rm -f $(OBJ) $(OBJ2) $(EXE) $(EXE2)


