# GTOPO30 UTILITIES

## PROJECT DESCRIPTION

This is a set of utilies for manipulating the GTOPO30 dataset. The GTOPO30 dataset is a 30 arc-second resolution elevation scan of the planet,
The full dataset can be found here: https://www.usgs.gov/centers/eros/science/usgs-eros-archive-digital-elevation-global-30-arc-second-elevation-gtopo30

## USAGE INSTRUCTIONS

### RUN 'make' TO CREATE ALL EXECUTABLES DISPLAYED FOLLOWING

### ELSE RUN 'make <executable>' TO CREATE THE EXECUTABLE YOU WANT

./gtopoEcho:
This program coppies a given dem file to another given dem file
Usage: Usage: ./gtopoEcho inputFile width height outputFile

./gtopoComp:
This program compares two dem files and will output wheter or not they are logically identical
Usage: ./gtopoComp firstFile width secondFile output

./gtopoReduce:
This program takes an input dem file and an integer factor and will reduce the image by that factor in each direction
Usage: ./gtopoReduce input width height reduction_factor output

./gtopoTile:
This program takes 3 arguments, an input dem file, an integer factor n, and an output file name template. It
divides the input file into nxn smaller images corresponding to parts of the image)
Usage: ./gtopoTile inputFile width height tiling*factor outputFile*<row>\_<column>

./gtopoAssemble:
This program takes 5n + 4 arguments, an output image with its width and height, and then a set of tiles and their
row and column where they should be inserted into the output image.
Usage: ./gtopoAssemble outputFile width height (row column inputFile width height)+

./gtopoPrintLand:
This takes an input file an output file and the sea height hill height and mountain height
and then prints a representation of the input files data, as an ascii image to output file.
Usage: ./gtopoPrintLand inputFile width height outputFile sea hill mountain

./gtopoAssembleReduce:
This file takes an number of input files, assembles them in memory, reduces them by the given
reduction factor and then outputs the reduced image into outputFile
Usage: ./gtopoAssembleReduce outputFile width height reduction_factor (row column inputFile width height)+
