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

// get the endianness reverser
#include "endianReverser.h"

// get the check int function
#include "checkInt.h"

// library for I/O routines      
#include <stdio.h>

// library for memory routines     
#include <stdlib.h>

// library for string manipulation
#include <string.h>

// functions to round and sqrt
#include "roundNumber.h"
#include "sqrtNumber.h"

int main(int argc, char **argv);
int assembler(char **arguments, int arg_length);
