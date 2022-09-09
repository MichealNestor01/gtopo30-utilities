#include "roundNumber.h"

// this function rounds a number to the nearest ten
int round_number(double number) {
    double decimal = number - (int) number;
    if (decimal == 0) {
        return (int) number;
    } else if (decimal < 0.5) {
        return (int) number;
    }
    return (int) (number + 1);
}
