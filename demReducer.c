// include the interface file
#include "demReducer.h"

//reduce actually reduces the dem file by the given factor
int dem_reducer(DEM * dem, int factor) {
    if (factor <= 0 || factor > dem->width || factor > dem->height) { //factor must be > 0 and cant be more then a dimensions of the image
        return ERROR_MISC_SCALEFACTOR;    
    }
    
    // old hight is used when reading data.
    int old_height = dem->height;
    // adjust the width and height by the given factor
    if (dem->width % factor != 0) {
        dem->width = (dem->width + factor) / factor;
    } else {
        dem->width = dem->width / factor;
    }
    if (dem->height % factor != 0) {
        dem->height = (dem->height + factor) / factor;
    } else {
        dem->height = dem->height / factor;    
    }
    
    // what I am going to do to reduce the image is to overwrite the existing 2d array:
    // Take this image data array and reduce it by factor 3 this would be the output:
    // (0)  1  2  (3)                    0  3  2  3                      0  3  2 3
    // 4    5  6  7      ===reduced===>  12 15 5  6   ===after free===>  12 15 5 6
    // 8    9  10 11                     8  9  10 11
    // (12) 13 14 (15)                   12 13 14 15
    // as the width and height have been adjusted the data on the end of row 1 and 2 will
    // be ignored and the data on rows 3 and 4 will be ignored however that means I will need
    // to free those rows here

    for (int r_index = 0; r_index < dem->height; r_index++) { // loop over each point in the new reduced array
        // current row in the original is r_index * height
        for (int p_index = 0; p_index < dem->width; p_index++) { // loop over each point in the new reduced row
            // overwrite the current value in the reduced raster with the corresponding value in the original.
            dem->image_data[r_index][p_index] = dem->image_data[r_index *  factor][p_index *  factor];
        }
    }

    // free the rows in image data that are no longer in use
    for (int r_index = old_height; r_index >= dem->height; r_index--){
        free(dem->image_data[r_index]);
    }

    // return without error
    return EXIT_NO_ERRORS;
}
