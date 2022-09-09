// dem struct deffinition 
#include "demStruct.h"

// exit codes
#include "exitCodes.h"

// get the reader function
#include "demReader.h"

// get the error writer function
#include "exitMessage.h"

// get the read from file function
#include "demReadFromFile.h"

// get the dem cleaner function
#include "demCleaner.h"

// get the utility for checking if a string is an int
#include "checkInt.h"

// library for I/O routines      
#include <stdio.h>

// library for memory routines     
#include <stdlib.h>


#ifndef main
int main(int argc, char **argv);
int write_land(char * filename, DEM * dem, int sea, int hill, int mountain);
#endif
