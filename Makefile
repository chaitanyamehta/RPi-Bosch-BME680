CC = g++
OPT = -O3
#OPT = -g
WARN = -Wall
CFLAGS = $(OPT) $(WARN) $(INC) $(LIB)

VPATH = ./BME680_driver

# List corresponding compiled object files here (.o files)
BUILD_OBJ = bme680_test.o i2c.o bme680.o
 
#################################

# default rule

all: bme680
	@echo "my work is done here..."


# rule for making bme680

bme680: $(BUILD_OBJ)
	$(CC) -o bme680 $(CFLAGS) $(BUILD_OBJ) -lm
	@echo "-----------DONE WITH bme680-----------"


# generic rule for converting any .cpp file to any .o file
 
.cc.o:
	$(CC) $(CFLAGS)  -c $*.cc

.cpp.o:
	$(CC) $(CFLAGS)  -c $*.cpp


# type "make clean" to remove all .o files plus the bme680 binary

clean:
	rm -f *.o bme680


# type "make clobber" to remove all .o files (leaves bme680 binary)

clobber:
	rm -f *.o