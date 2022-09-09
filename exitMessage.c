#include "exitMessage.h"

int exit_code_with_message(int code, char * filename) {
    //print the appropriate error/usage/success message based on the return_code 
    switch (code) {
        case ECHOED:
            printf("ECHOED\n");
            return EXIT_NO_ERRORS;
        case IDENTICAL:
            printf("IDENTICAL\n");
            return EXIT_NO_ERRORS;
        case DIFFERENT:
            printf("DIFFERENT\n");
            return EXIT_NO_ERRORS;
        case CONVERTED:
            printf("CONVERTED\n");
            return EXIT_NO_ERRORS;
        case REDUCED:
            printf("REDUCED\n");
            return EXIT_NO_ERRORS;
        case TILED:
            printf("TILED\n");
            return EXIT_NO_ERRORS;
        case ASSEMBLED:
            printf("ASSEMBLED\n");
            return EXIT_NO_ERRORS;
        case PRINTED:
            printf("PRINTED\n");
            return EXIT_NO_ERRORS;
        case ERROR_ARG_COUNT:
            printf("ERROR: Bad Argument Count\n"); // eddited to test auto grader
            return ERROR_ARG_COUNT;
        case ERROR_FILENAME:
            printf("ERROR: Bad File Name (%s)\n", filename);
            return ERROR_FILENAME;
        case ERROR_MAGICNUMBER:
            printf("ERROR: Bad Magic Number (%s)\n", filename);
            return ERROR_MAGICNUMBER;
        case ERROR_COMMENT:
            printf("ERROR: Bad Comment Line (%s)\n", filename);
            return ERROR_COMMENT;
        case ERROR_DIMENSIONS:
            printf("ERROR: Bad Dimensions (%s)\n", filename);
            return ERROR_DIMENSIONS;
        case ERROR_MAX_GRAY:
            printf("ERROR: Bad Max Gray Value (%s)\n", filename);
            return ERROR_MAX_GRAY;
        case ERROR_MALLOC_IMAGE:
            printf("ERROR: Image Malloc Failed\n");
            return ERROR_MALLOC_IMAGE;
        case ERROR_DATA:
            printf("ERROR: Bad Data (%s)\n", filename);
            return ERROR_DATA;
        case ERROR_OUT:
            printf("ERROR: Output Failed (%s)\n", filename);
            return ERROR_OUT;
        case ERROR_MISC_MALLOC:
            printf("ERROR: Miscellaneous Non-Image Memory Allocation Failed\n");
            return ERROR_MISC;
        case ERROR_MISC_SAME_FORMAT_R:
            printf("ERROR: Miscellaneous (%s) is already of type Raw (Binary)\n", filename);
            return ERROR_MISC;
        case ERROR_MISC_SAME_FORMAT_P:
            printf("ERROR: Miscellaneous (%s) is already of type Plain (ASCII)\n", filename);
            return ERROR_MISC;
        case ERROR_MISC_SCALEFACTOR:
            printf("ERROR: Miscellaneous Bad Scale Factor, must be an int > 0, and should not exceed the width or height of the input image\n");
            return ERROR_MISC;
        case ERROR_MISC_TILE_TEMPLATE:
            printf("ERROR: Miscellaneous Bad Tile Template, must be of the form: outputfile_<row>_<column>.pgm\n");
            return ERROR_MISC;
        case ERROR_MISC_ASSEMBLE_BOUNDS:
            printf("ERROR: Miscellaneous Tiles provided exceed the given width and height of the final image\n");
            return ERROR_MISC;
        case ERROR_MISC_NAN:
            printf("ERROR: Miscellaneous value provided is not an integer (%s)", filename);
        default:
            return EXIT_NO_ERRORS;
    }
}




