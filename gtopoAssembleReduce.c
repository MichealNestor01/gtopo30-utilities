/*
======DEM ASSEMBLE REDUCE MODULE======
Author: Micheal Nestor
Date Created: 25/05/22 
Email: sc21mpn@leeds.ac.uk
Purpose: This file will take dem tiles and assemble them in ram and reduce them in ram, then output the reduced image
*/

// prototypes and dependencies for this file
#include "gtopoAssembleReduce.h"

// as assemble will be ran directly it uses a main function
int main(int argc, char **argv) {
    // return code will be the int returned at the end by main, it is used to track errors
    int return_code = EXIT_NO_ERRORS;

    // verify the arguments
    if (argc == 1) { // no arguments given
        // print the usage message and return without error
        printf("Usage: %s outputFile width height reduction_factor (row column inputFile width height)+\n", argv[0]);
        return EXIT_NO_ERRORS;
    } else if (argc % 5 != 0) { // check there is the correct number of arguments: 4 + 5n 
        // adjust return code and go to end of function 
        return exit_code_with_message(ERROR_ARG_COUNT, NULL);
    }

    // check that argv[2], argv[3] and argv[4] are ints
    return_code = check_int(argv[2]);
    if (return_code != EXIT_NO_ERRORS)
        return exit_code_with_message(return_code, NULL);
    return_code = check_int(argv[3]);
    if (return_code != EXIT_NO_ERRORS)
        return exit_code_with_message(return_code, NULL);
    return_code = check_int(argv[4]);
    if (return_code != EXIT_NO_ERRORS)
        return exit_code_with_message(ERROR_MISC_NAN, NULL);

    // run assembler function to assemble the image
    return_code = assemble_reduce(argv, argc);

    // return with correct code and message
    return exit_code_with_message(return_code, NULL);       
}

// this function actually assembles the given tiles and reduces them 
int assemble_reduce(char **arguments, int arg_length) {
    int return_code = EXIT_NO_ERRORS;
    
    // get the number of args that are describing input files
    int total_args = arg_length-5;

    // total tiles is the total number of tiles that have been given
    int total_tiles = total_args/5;
    
    // get master dem widht and height from the aguments
    int width = atoi(arguments[2]);
    int height = atoi(arguments[3]);

    // Create a dem for struct for the assembled image hensforth the master_image
    DEM * master_image = (DEM *) malloc(sizeof(DEM));
    // check malloc worked
    if (master_image == NULL) // if it didn't return an error
        return ERROR_MISC_MALLOC;
    // initialise the master dem's values
    master_image->height = height;
    master_image->width = width;
    // allocate memory for the image data 
    master_image->image_data = (unsigned short **) malloc(height * sizeof(unsigned short *));
    // check malloc worked
    if (master_image->image_data == NULL) // if it didn't return an error
        return ERROR_MALLOC_IMAGE;
    // allocate memory to the master images image data
    for (int row_index = 0; row_index < height; row_index++) {
        // allocate memory to each row in the master dem image
        master_image->image_data[row_index] =  (unsigned short *) malloc(width * sizeof(unsigned short));
        // check if malloc failed
        if (master_image->image_data == NULL) // if it did return an error
            return ERROR_MALLOC_IMAGE; 
        // populate the dem with black pixels
        for (int col_index = 0; col_index < width; col_index++) {
            master_image->image_data[row_index][col_index] = (unsigned short) 0;
        }
    }

    // loop over all of the arguments given and add the corresponding tile to the master image 
    for (int argument_index = 0; argument_index < total_tiles; argument_index ++) {
        // get data about the current tile fron the given arguments, example each row is at index 5(n+1)
        char * current_filename = arguments[5 * (argument_index + 1) + 2];
        int row = atoi(arguments[5 * (argument_index + 1)]); 
        int col = atoi(arguments[5 * (argument_index + 1) + 1]);
	    int current_width = atoi(arguments[5 * (argument_index + 1) + 3]);
	    int current_height = atoi(arguments[5 * (argument_index + 1) + 4]);
        
        // create a temp dem for the current tile
        DEM * temp_dem = (DEM *) malloc(sizeof(DEM));
        // if malloc fails return an error
        if (temp_dem == NULL) 
            return ERROR_MISC_MALLOC;
	    // asign the dem's width and height given in the arguments
	    temp_dem->width = current_width;
	    temp_dem->height = current_height;
        // now read the data from the given file
        return_code = read_from_file(current_filename, temp_dem);
        if (return_code != EXIT_NO_ERRORS)
            return return_code;
        // check if this dem will fit
        if (temp_dem->width + col > width || temp_dem->height + row > height) {
            return ERROR_MISC_ASSEMBLE_BOUNDS; // Gonna need to make a new error for this
        }
        // dump this images pixels into the master dem by copying them to the correct place
        for (int row_index = 0; row_index < temp_dem->height; row_index++) {
            for (int col_index = 0; col_index < temp_dem->width; col_index++) {
                master_image->image_data[row_index + row][col_index + col] = temp_dem->image_data[row_index][col_index];
            }
        }
        // clean up the temp dem's data
        dem_cleaner(temp_dem);
    }
    
    // now reduce the master image
    return_code = dem_reducer(master_image, atoi(arguments[4]));
    if (return_code != EXIT_NO_ERRORS)
        return return_code;
    
    // now write reduced dem to a file
    return_code = write_to_file(arguments[1], master_image);
    if (return_code != EXIT_NO_ERRORS)
        return return_code;
           
    // clean up the master dem's memory 
    dem_cleaner(master_image);  
    
    // return with the assembled return code 
    return ASSEMBLE_REDUCED;
}
