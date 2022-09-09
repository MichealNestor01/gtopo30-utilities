/*
======DEM WRITER MODULE======
Author: Micheal Nestor
Date Created: 24/05/22
Email: sc21mpn@leeds.ac.uk
Purpose: This file will take a dem struct and convert this data to a dem file
*/

// prototypes and dependencies for this file
#include "demWriter.h"

// writer writes the image data to the file in the form of binary bytes
int writer(FILE * output_file, DEM * dem) {
    // bytes_written is used to track whether the fwrite works
    size_t bytes_written = -1;
   
    // write to file
    for (int r_index = 0; r_index < dem->height; r_index++) { // loop over each row in image data
        //swap the endianness of each bit in the current row
        for (int c_index = 0; c_index < dem->width; c_index++) { // c index refers to column index
            dem->image_data[r_index][c_index] = endian_reverser(dem->image_data[r_index][c_index]);
        }
        
        // write the current row to the file
        bytes_written = fwrite(dem->image_data[r_index], 2, dem->width, output_file);
        // sanity check the data being written
        if (bytes_written != dem->width) { //data write failed
            // return error with output
            return ERROR_OUT;                   
        }
    }
    //return wihout error 
    return EXIT_NO_ERRORS;
}
