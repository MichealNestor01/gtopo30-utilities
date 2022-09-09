// dem struct deffinition 
#include "demStruct.h"

// exit codes
#include "exitCodes.h"

// global constants
#include "demConstants.h"

// endian reverser
#include "endianReverser.h"

// library for I/O routines      
#include <stdio.h>

// library for memory routines     
#include <stdlib.h>


#ifndef reader
int reader(FILE * input_file, DEM * dem);
int read_image_data(FILE * input_file, DEM * dem);
int read_binary_data(FILE * input_file, DEM * dem);
#endif
