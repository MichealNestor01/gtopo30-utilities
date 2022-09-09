// dem struct deffinition
#include "demStruct.h"

// exit codes
#include "exitCodes.h"

// get the reader function
#include "demWriter.h"

// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// prototypes
int write_to_file(char * filename, DEM * dem);
