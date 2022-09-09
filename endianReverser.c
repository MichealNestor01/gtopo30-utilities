#include "endianReverser.h"

unsigned short endian_reverser(unsigned short wrong_way) {
    // the integer we want to reverse, stored as two bytes in an array.
    unsigned char wrong_way_bytes[2];

    // a second array to hold the output
    unsigned char right_way_bytes[2];

    // now copy the bytes into the array
    wrong_way_bytes[0] = wrong_way % 256;
    wrong_way_bytes[1] = wrong_way / 256;

    // now reverse them
    right_way_bytes[0] = wrong_way_bytes[1];
    right_way_bytes[1] = wrong_way_bytes[0];

    // return the reassembled short:
    return (unsigned short) right_way_bytes[1] * 256 + right_way_bytes[0];
}
