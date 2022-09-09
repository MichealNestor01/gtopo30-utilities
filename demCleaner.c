// include the header file
#include "demCleaner.h"

// This function cleans up the memory of the dem struct it is passed  
void dem_cleaner(DEM * dem) {
    // Cleanup memory
    if (dem->image_data != NULL) {
        // loop over and free rows workng backwards
        for (int r_index = dem->height - 1; r_index >= 0; r_index--) {
            if (dem->image_data[r_index] != NULL) {
                free(dem->image_data[r_index]);
            }
        }
        free(dem->image_data);
    } 
    if (dem != NULL) {
        free(dem);
    }
}
