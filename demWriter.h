// dem struct deffinition 
#include "demStruct.h"

// exit codes
#include "exitCodes.h"

// global constants
#include "demConstants.h"

// endianess reverser
#include "endianReverser.h"

// library for I/O routines      
#include <stdio.h>

// library for memory routines     
#include <stdlib.h>


#ifndef writer
int writer(FILE * output_file, DEM * dem);
#endif
