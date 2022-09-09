/*
======GTOPO PRINT LAND MODULE======
Author: Micheal Nestor
Date Created: 25/05/22
Email: sc21mpn@leeds.ac.uk
Purpose: This file will take a dem input file, and attempt to output the data as a textabsed image in the command line
*/

// prototypes and dependencies for this file
#include "gtopoPrintLand.h"

// as print land will be run directly it uses a main function
int main(int argc, char **argv) {
    // verify the argument count:
    if (argc == 1) { // no arguments given
	    // print usage code and return without error
	    printf("Usage: %s inputFile width height outputFile sea hill mountain\n", argv[0]);
	    return EXIT_NO_ERRORS;
    }  else if (argc != 8) { // incorrect argument count 
	    // adjust return code and go to the end of the function
	    return exit_code_with_message(ERROR_ARG_COUNT, NULL);
    }

    // the struct will be what stores the dem file's data
    DEM * dem = (DEM * ) malloc(sizeof(DEM));
    // verify that the memory was allocated correctly
    if (dem == NULL) // malloc failed so return malloc error code and message
	    return exit_code_with_message(ERROR_MISC_MALLOC, NULL);
    
    int return_code;
    // check that width and height are intsa
    for (int arg_index = 2; arg_index < 4; arg_index++) {
        return_code = check_int(argv[arg_index]);
        if (return_code != EXIT_NO_ERRORS)
            return exit_code_with_message(return_code, argv[2]);
    }
    
    // check that the sea hill and mountain are ints
    for (int arg_index = 5; arg_index < 8; arg_index++) {
        return_code = check_int(argv[arg_index]);
        if (return_code != EXIT_NO_ERRORS)
            return exit_code_with_message(ERROR_MISC_NAN, argv[arg_index]);
    }

    // with and height are ints
    dem->width = atoi(argv[2]);
    dem->height = atoi(argv[3]); 

    // get the data from the file into the the dem struct
    return_code = read_from_file(argv[1], dem);
    if (return_code == EXIT_NO_ERRORS) // there was no error reading data, so now try and copy the data to the output file
    	return_code = write_land(argv[4], dem, atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
    
    // clean memory allocated to dem:
    dem_cleaner(dem);
    
    //return correct code with a message:
    if (return_code == ERROR_OUT) 
        return exit_code_with_message(return_code, argv[4]);
    return exit_code_with_message(PRINTED, argv[1]);
}

int write_land(char * filename, DEM * dem, int sea, int hill, int mountain) {
    // verify the given output file exists and create file pointer to that file 
    FILE * output_file = fopen(filename, "w");
    // check that the file opening worked
    if (output_file == NULL) {
        return ERROR_OUT;
    }

    // bytes written is uesed to track whether fprints work
    size_t bytes_written = -1;
    
    // loop over the data in the dem and write the correct corresponding character to the file
    for (int r_index = 0; r_index < dem->height; r_index++) {
        for (int c_index = 0; c_index < dem->width; c_index++) {
            //cast to short so we can get the two's complement representation of the height
            short current_height = (short) dem->image_data[r_index][c_index];
            // current char will be set to ' ', ., ^ or A
            char current_char;
            if (current_height < sea) {
                current_char = ' ';
            } else if (current_height < hill) {
                current_char = '.';
            } else if (current_height < mountain) {
                current_char = '^';
            } else {
                current_char = 'A';
            }
            // print the current character to the file
            bytes_written = fprintf(output_file, "%c", current_char);
            if (bytes_written < 0) {
                // return there is an issue with the output
                return ERROR_OUT;
            }
        }
        //print a line break at the end of each line
        fprintf(output_file, "\n");
    }
    
    // close the file pointer 
    fclose(output_file); 

    return EXIT_NO_ERRORS;
}








