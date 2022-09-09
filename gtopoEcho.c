/*
======GTOPO ECHO MODULE======
Author: Micheal Nestor
Date Created: 24/05/22
Email: sc21mpn@leeds.ac.uk
Purpose: This file will take a dem input file, and an output file name, and then it will copy the data from the input to the output
*/

// prototypes and dependencies for this file
#include "gtopoEcho.h"

// as echo will be run directly it uses a main function
int main(int argc, char **argv) {
    // verify the argument count:
    if (argc == 1) { // no arguments given
	    // print usage code and return without error
	    printf("Usage: %s inputFile width height outputFile\n", argv[0]);
	    return EXIT_NO_ERRORS;
    }  else if (argc != 5) { // incorrect argument count 
	    // adjust return code and go to the end of the function
	    return exit_code_with_message(ERROR_ARG_COUNT, NULL);
    }

    // the struct will be what stores the dem file's data
    DEM * dem = (DEM * ) malloc(sizeof(DEM));
    // verify that the memory was allocated correctly
    if (dem == NULL) // malloc failed so return malloc error code and message
	    return exit_code_with_message(ERROR_MISC_MALLOC, NULL);
    
    // check that width and height are ints
    int return_code = check_int(argv[2]);
    if (return_code != EXIT_NO_ERRORS)
        return exit_code_with_message(return_code, argv[2]);
    return_code = check_int(argv[3]);
    if (return_code != EXIT_NO_ERRORS)
        return exit_code_with_message(return_code, argv[3]);
    
    // with and height are ints
    dem->width = atoi(argv[2]);
    dem->height = atoi(argv[3]); 

    // get the data from the file into the the dem struct
    return_code = read_from_file(argv[1], dem);
    if (return_code == EXIT_NO_ERRORS) // there was no error reading data, so now try and copy the data to the output file
    	return_code = write_to_file(argv[4], dem);
    
    // clean memory allocated to dem:
    dem_cleaner(dem);
    
    //return correct code with a message:
    if (return_code == ERROR_OUT) 
        return exit_code_with_message(return_code, argv[4]);
    return exit_code_with_message(ECHOED, argv[1]);
}
