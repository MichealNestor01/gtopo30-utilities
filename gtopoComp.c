/*
======GTOPO COMP MODULE======
Author: Micheal Nestor
Date Created: 24/05/22
Email: sc21mpn@leeds.ac.uk
Purpose: This file will take two dem files as attributes, compare them, and decide if they are logically equivalent
*/

// prototypes and dependencies for this file
#include "gtopoComp.h"

int main(int argc, char **argv) {
    // verify the argumen count
    if (argc == 1) { // no arguments given
	    // print usage code and return without error
	    printf("Usage: %s firstFile width height secondFile\n", argv[0]);
        // return without error
        return EXIT_NO_ERRORS;
    } else if (argc != 5) { // incorrect argument count
        // return the correct error code, and print the correct error message
        return exit_code_with_message(ERROR_ARG_COUNT, NULL);
    }
    
    // allocate memory to the structs that will store data about both files
    DEM * dem_a = (DEM *) malloc(sizeof(DEM));
    DEM * dem_b = (DEM *) malloc(sizeof(DEM));
    // verify memory was allocated correctly
    if (dem_a == NULL || dem_b == NULL) // malloc failed so exit program
        return exit_code_with_message(ERROR_MISC_MALLOC, NULL);
    
    // check if width and height are ints
    int return_code = check_int(argv[2]);
    if (return_code != EXIT_NO_ERRORS)
        return exit_code_with_message(ERROR_MISC_NAN, argv[2]);
    return_code = check_int(argv[3]);
    if (return_code != EXIT_NO_ERRORS)
        return exit_code_with_message(ERROR_MISC_NAN, argv[3]);

    // set the width and height of the two dem structs
    dem_a->width = atoi(argv[2]); 
    dem_b->width = atoi(argv[2]);
    dem_a->height = atoi(argv[3]);
    dem_b->height = atoi(argv[3]);

    // now try and read data to these dem's
    return_code = read_from_file(argv[1], dem_a);
    if (return_code != EXIT_NO_ERRORS) { // There was an error reading data from the first file
        dem_cleaner(dem_a);
        return exit_code_with_message(return_code, argv[1]);
    }
    return_code = read_from_file(argv[4], dem_b);
    if (return_code != EXIT_NO_ERRORS) { // There was an error reading data from the second file
        dem_cleaner(dem_a);
        dem_cleaner(dem_b);
        return exit_code_with_message(return_code, argv[4]);
    }

    // now compare the two files to determine if they are logically equivalent   
    return_code = compare_dems(dem_a, dem_b) == 1 ? IDENTICAL : DIFFERENT;    
    
    // clean the dems
    dem_cleaner(dem_a);
    dem_cleaner(dem_b);
    
    // return the correct code and print the correct message   
    return exit_code_with_message(return_code, NULL);
}

// this function will return 1 if the two dems are logically equivalent 0 else
int compare_dems(DEM * dem_a, DEM * dem_b) {
    // check that both dems have the same dimensions
    if (dem_a->width != dem_b->width || dem_a->height != dem_b->height)
        return 0;        
    // compare the pixel values in each dem    
    for (int r_index = 0; r_index < dem_a->height; r_index ++) { // loop over the rows in the dems 
        for (int p_index = 0; p_index < dem_a->width; p_index ++) { // loop over the pixels in each row
            if (dem_a->image_data[r_index][p_index] != dem_b->image_data[r_index][p_index]) { // corresponding pixels are not identical
                return 0;
            }
        }
    }
    // return identical
    return 1;
}
