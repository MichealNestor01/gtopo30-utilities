#include "checkInt.h"

// check the given string is an int
int check_int(char * string) {
    for (int c = 0; c < strlen(string); c++) { // loop over each character in the string
        int current_char = (int) string[c]; // cast the current character to an int getting its ascii index
        if (current_char < 48 || current_char > 57) { // if the ascii index is not between 48 and 57 then it isnt a digit
            // printf("Current char: %d\tint val:%d\n", string[c], current_char);
            return ERROR_MISC_NAN; 
        }    
    }
    return EXIT_NO_ERRORS;    
}
