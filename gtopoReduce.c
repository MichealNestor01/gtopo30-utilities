/*
======DEM REDUCE MODULE======
Author: Micheal Nestor
Date Created: 24/05/22
Email: sc21mpn@leeds.ac.uk
Purpose: This file will take a dem input file, an output file name and a reduction factor. It will then 
store the input file reduced by the factor in the output file
*/

// prototypes and dependencies for this file
#include "gtopoReduce.h"

// as reduce will be run directly it uses a main function
int main(int argc, char **argv) {
    // verify the arguments:
    if (argc == 1) { // no arguments given
	    // print usage code and return without error
	    printf("Usage: %s input width height reduction_factor output\n", argv[0]);
	    return EXIT_NO_ERRORS;
    }  else if (argc != 6) { // incorrect argument count 
	    // adjust return code and go to the end of the function
	    return exit_code_with_message(ERROR_ARG_COUNT, NULL);
    }  

    // check that arg[2] arg[3] and arg[4] are an integers
    int return_code = check_int(argv[4]); 
    if (return_code != EXIT_NO_ERRORS)
        return exit_code_with_message(return_code, NULL);
    return_code = check_int(argv[3]);
    if (return_code != EXIT_NO_ERRORS)
        return exit_code_with_message(ERROR_MISC_NAN, argv[2]);
    return_code = check_int(argv[2]);
    if (return_code != EXIT_NO_ERRORS)
        return exit_code_with_message(ERROR_MISC_NAN, argv[3]);


    // the struct will be what stores the dem file's data
    DEM * dem = (DEM * ) malloc(sizeof(DEM));
    // verify that the memory was allocated correctly
    if (dem == NULL) // malloc failed so return with correct errro code and a message
        return exit_code_with_message(ERROR_MISC_MALLOC, NULL);

    // initialise the value of the width and height
    dem->width = atoi(argv[2]);
    dem->height = atoi(argv[3]);


    // get the data from the file into the dem struct
    return_code = read_from_file(argv[1], dem);
    if (return_code == EXIT_NO_ERRORS) {// there was no error reading data, so now try and copy the data to the output file
        return_code = dem_reducer(dem, atoi(argv[4]));
        if (return_code == EXIT_NO_ERRORS) 
            return_code = write_to_file(argv[5], dem);    
    }
 
    // clean up memory
    dem_cleaner(dem);

    if (return_code == ERROR_OUT)
        return exit_code_with_message(return_code, argv[5]);
    else if (return_code != EXIT_NO_ERRORS)
        return exit_code_with_message(return_code, argv[1]);
    return exit_code_with_message(REDUCED, NULL);
}
