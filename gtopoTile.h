// dem struct deffinition 
#include "demStruct.h"

// exit codes
#include "exitCodes.h"

// get the error writer function
#include "exitMessage.h"

// get the read from file function
#include "demReadFromFile.h"

// get the write to file function
#include "demWriteToFile.h"

// get the dem cleaner function
#include "demCleaner.h"

// get the check int function
#include "checkInt.h"

// get the endian reverser function 
#include "endianReverser.h" 

// library for I/O routines      
#include <stdio.h>

// library for memory routines     
#include <stdlib.h>

// library for string manipulation
#include <string.h>

// include function for rounding
#include "roundNumber.h"

int main(int argc, char **argv);
int split(DEM * dem, int factor, char * output_file);
int check_output_format(char * string);
