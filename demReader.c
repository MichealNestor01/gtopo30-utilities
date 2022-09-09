/*
======DEM READER MODULE======
Author: Micheal Nestor
Date Created: 02/03/22
Email: sc21mpn@leeds.ac.uk
Purpose: This file will verify and read the data from a dem file and return a pointer to a struct containing this data
*/

// prototypes and dependencies for this file
#include "demReader.h"

// reader will take the given file, and demStruct and will populate the struct with the files data 
int reader(FILE * input_file, DEM * dem) {
    // sanity check input_file
    if (input_file == NULL) {
        // return with bad filename error code
        return ERROR_FILENAME;
    }

    // Read the dem's image data
    return  read_image_data(input_file, dem);
}

//===IMAGE DATA READING FUNCTIONS===//

// this attempts to read the image data from a dem file
int read_image_data(FILE * input_file, DEM * dem) {
    int return_code = EXIT_NO_ERRORS;
    // allocate memory to the dem struct's image data
    dem->image_data = NULL;
    // allocate unsigned char * size of height to dem->image_data
    // allocate to each of them unsigned char size of width to each in dem->image_data
    dem->image_data = (unsigned short **) malloc(dem->height * sizeof(unsigned short *));
    // sanity check the memory allocation
    if (dem->image_data == NULL) { // malloc failed
        // Return with relevant error code
        return ERROR_MALLOC_IMAGE;
    }
    for (int i = 0; i < dem->height; i++) {
        dem->image_data[i] = (unsigned short *) malloc(dem->width * sizeof(unsigned short *));
        // sanity check memory allocation
        if (dem->image_data[i] == NULL) {//malloc failed
            // return with malloc fail error code
            return ERROR_MALLOC_IMAGE;
        }
    }
    
    // read the image data   
    return_code = read_binary_data(input_file, dem);
    
    if (return_code != EXIT_NO_ERRORS) { // there was an error reading the image data 
        return return_code;
    } 
     
    // now check to see whether all of the data has been read from the file (it should have been)
    unsigned char * excess_data = (unsigned char *) malloc(1);
    if (excess_data == NULL) { // malloc failed
	    // return miscilaneous error code
	    return ERROR_MISC_MALLOC;	
    } 
    // attempt to read data from the file 
    // read any white space 
    int scan_count = fscanf(input_file, " ");
    scan_count = fread(excess_data, 1, 1, input_file);
    // clean memory
    free(excess_data);
    if (scan_count > 0) { // something has been scanned, there fore there is too much data in the file
	    // return with teh bad image data error code
	    return ERROR_DATA;
    }
  
    // return the no errors exit code	
    return EXIT_NO_ERRORS;
}

// reads image data encoded as binary in a dem file
int read_binary_data(FILE * input_file, DEM * dem) {
    // read the binary data into each row of dem->image_data
    for (int r_index = 0; r_index < dem->height; r_index++) {
        // read the binary data
        int scan_count = fread(dem->image_data[r_index], 2, dem->width, input_file);
        // verify the image data
        if (scan_count != dem->width) { // check the correct  number of bits was read
            // return with the error data code
            return ERROR_DATA;            
        } else {
            // now reverse the endianness of the data
            for (int p_index = 0; p_index < dem->width; p_index++) { // reverse each pixel
                dem->image_data[r_index][p_index] = endian_reverser(dem->image_data[r_index][p_index]);
                if (dem->image_data[r_index][p_index] < SEA_LEVEL) { 
                    // return with data error code
                    return ERROR_DATA;
                }
            }
        }
    }
    return EXIT_NO_ERRORS;
}
