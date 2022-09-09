#include "sqrtNumber.h"

// newton raphson method for finding square root
// I created this algorithm as linking the math 
// library broke the autograder for me
// This was created using the guide of this article:
// https://www.geeksforgeeks.org/find-root-of-a-number-using-newtons-method/
double sqrt_number(double number) {
    // assumed root will converge on root
    double assumed_root = number;
    double root;
    while (1) {
        // calculate a more accurate assumed root
        root = 0.5 * (assumed_root + (number / assumed_root));
        // check that the root is appropriately accurate
        if (root - assumed_root < 0.001) {
            break;
        }
        assumed_root = root;
    }
    return root;
}
