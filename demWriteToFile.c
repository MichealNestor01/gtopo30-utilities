#include "demWriteToFile.h"

// Function used by multiple files to read from a file 
int write_to_file(char * filename, DEM * dem) {
    // verify the given output file name exists and create file pointer to that file
    FILE * output_file = fopen(filename, "w");
    // check that the file opening worked 
    if (output_file == NULL) { // NULL output file 
	    // adjust the return code to bad output file
    	return ERROR_OUT;
    }
		
    int return_code = EXIT_NO_ERRORS;
    // write the read data to the given output file
    return_code = writer(output_file, dem);
    // close the file
    if (output_file == NULL) {
        printf("output is null\n");
    } else {
        fclose(output_file);
    }
    // return the writer's return code
    return return_code;
}
