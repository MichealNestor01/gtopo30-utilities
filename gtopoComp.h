// dem struct deffinition 
#include "demStruct.h"

// exit codes
#include "exitCodes.h"

// global constants
#include "demConstants.h"

// get the read from file function
#include "demReadFromFile.h"

// get the dem memory cleaner function
#include "demCleaner.h"

// get the the check int function
#include "checkInt.h"

// get the error printer function
#include "exitMessage.h"

// library for I/O routines      
#include <stdio.h>

// library for memory routines     
#include <stdlib.h>

int main(int argc, char **argv);
int compare_dems(DEM * dem_a, DEM * dem_b);

