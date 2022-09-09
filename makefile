#
# Author: Micheal Nestor
# Date created: 24/05/22
#
# Make file for assignment two
#

# Flags:
#  -E 			preproces only (use .i for output)
#  -c			compile only
#  -g			debug support for gdb
#  -std=c99		use the C99 C standard
#  -fmax-errors=1	stop the compiler after one error
#  -o <FILENAME>	output file name
#  -Wall		turn all warnings on
#  -Werror		treat all warnings as errors
#  -lm 			link the math library


# Macros to add details:
# first a macro for the compiler name
CC = gcc
# now a macro for the compile flags
CCFLAGS = -g -std=c99 -fmax-errors=1 -Wall -Werror # -lm
# The set of subordinate routines and then grouped by which are dependent on which
MODULES_LIST = demReader.o exitMessage.o demCleaner.o demReadFromFile.o checkInt.o endianReverser.o demWriter.o demWriteToFile.o roundNumber.o sqrtNumber.o
MODULES_ECHO = exitMessage.o demCleaner.o demReadFromFile.o demReader.o checkInt.o endianReverser.o  demWriteToFile.o demWriter.o
MODULES_COMP = demReader.o exitMessage.o demCleaner.o demReadFromFile.o endianReverser.o checkInt.o
MODULES_REDUCE = demWriter.o exitMessage.o demCleaner.o demReadFromFile.o demReader.o demWriteToFile.o checkInt.o endianReverser.o demReducer.o
MODULES_TILE = ${MODULES_REDUCE} roundNumber.o
MODULES_ASSEMBLE = ${MODULES_TILE} sqrtNumber.o
MODULES_ASSEMBLE_REDUCE = ${MODULES_ASSEMBLE}
# the set of main routines 
MAINS = gtopoEcho.o gtopoComp.o gtopoReduce.o gtopoTile.o gtopoAssemble.o gtopoPrintLand.o gtopoAssembleReduce.o
# the set of executables
TARGETS = gtopoEcho gtopoComp gtopoReduce gtopoTile gtopoAssemble gtopoPrintLand gtopoAssembleReduce


# First target is the default
# we will use a dummy target to fource compilation of multiple executables
all: ${TARGETS}
# note the empty command - we don't do "anything" except check dependencies

# next, a dummy target to clean things up
# This is in case the cmpilation gets confused 
# This has no dependencies at all, and always executes
clean:
	rm ${TARGETS} ${MAINS} ${MODULES_LIST} 

# The demEcho executable depends on it's own file and the standard set of modules
# target	implementation
gtopoEcho:	gtopoEcho.o 	${MODULES_ECHO}
#	tool	compile flags	output name			files to compile
	${CC} 	${CCFLAGS}		-o gtopoEcho		gtopoEcho.o ${MODULES_ECHO}

# target	implementation
gtopoComp:	gtopoComp.o 	${MODULES_COMP}
#	tool	compile flags	output name			files to compile
	${CC} 	${CCFLAGS}		-o gtopoComp		gtopoComp.o ${MODULES_COMP}

# target	implementation
gtopoReduce: gtopoReduce.o 	${MODULES_REDUCE}
#	tool	compile flags	output name			files to compile
	${CC}	${CCFLAGS}		-o gtopoReduce		gtopoReduce.o ${MODULES_REDUCE}	

# target	implementation
gtopoTile:	gtopoTile.o 	${MODULES_TILE}
#	tool	compile flags	output name			files to compile
	${CC}	${CCFLAGS}		-o gtopoTile		gtopoTile.o ${MODULES_TILE}	

# target	implementation
gtopoAssemble:	gtopoAssemble.o ${MODULES_ASSEMBLE}
#	tool	compile flags	output name			files to compile
	${CC}	${CCFLAGS}		-o gtopoAssemble	gtopoAssemble.o ${MODULES_ASSEMBLE}	

# target 	implementation
gtopoPrintLand: gtopoPrintLand.o ${MODULES_ECHO}
#	tool	compile flags	output name			files to compile
	${CC}	${CCFLAGS}		-o gtopoPrintLand	gtopoPrintLand.o ${MODULES_ECHO}

# target 	implementation
gtopoAssembleReduce: gtopoAssembleReduce.o ${MODULES_ASSEMBLE_REDUCE}
#	tool	compile flags	output name 		files to compile 
	${CC}	${CCFLAGS}		-o gtopoAssembleReduce gtopoAssembleReduce.o ${MODULES_ASSEMBLE_REDUCE}

# Target for each object file 
# Each object file depends on its own implementation (.c)
# and any interfaces (.h) that it uses

# first the modules with the main routines
# Echo program:
# target	implementation				interfaces
gtopoEcho.o: 	gtopoEcho.c				gtopoEcho.h 
# 	tool	compile flags	output name			files to compile
	gcc 	-c ${CCFLAGS}	-o gtopoEcho.o		gtopoEcho.c

# Compare program
# target	implementation				interfaces
gtopoComp.o: gtopoComp.c				gtopoComp.h 
# 	tool	compile flags	output name			files to compile
	gcc 	-c ${CCFLAGS}	-o gtopoComp.o		gtopoComp.c

# Reduce image program
# target		implementation			interfaces
gtopoReduce.o: 	gtopoReduce.c			gtopoReduce.h 
# 	tool	compile flags	output name			files to compile
	gcc 	-c ${CCFLAGS}	-o gtopoReduce.o	gtopoReduce.c

# Reduce image program
# target		implementation			interfaces
gtopoTile.o: 	gtopoTile.c				gtopoTile.h 
# 	tool	compile flags	output name			files to compile
	gcc 	-c ${CCFLAGS}	-o gtopoTile.o		gtopoTile.c

# Assemble image program 
# target		implementation			interfaces
gtopoAssemble.o: 	gtopoAssemble.c	 	gtopoAssemble.h 
# 	tool	compile flags	output name			files to compile
	gcc 	-c ${CCFLAGS}	-o gtopoAssemble.o	gtopoAssemble.c

# print land program
# target		implementation			interfaces
gtopoPrintLand.o: gtopoPrintLand.c 		gtopoPrintLand.h
# 	tool 	compile flags 	output name 		files to compile
	gcc 	-c ${CCFLAGS}	-o gtopoPrintLand.o gtopoPrintLand.c

# assemble and reduce program
# target		implementation 			interfaces
gtopoAssembleReduce.o: gtopoAssembleReduce.c gtopoAssembleReduce.h
#	tool 	compile flags 	output name			files to compile
	gcc 	-c ${CCFLAGS}	-o gtopoAssembleReduce.o gtopoAssembleReduce.c

# module that reduces dem files
# target		implementation 			interfaces
demReducer.o:	demReducer.c			demReducer.h
#	tool 	compile flags	output name			files to compile
	gcc 	-c ${CCFLAGS}	-o demReducer.o 	demReducer.c

# now the module with the reader code
# target		implementation			interfaces
demReader.o: 	demReader.c				demReader.h 
# 	tool	compile flags	output name			files to compile
	gcc 	-c ${CCFLAGS}	-o demReader.o		demReader.c

# now with the writer code
# target		implementation			interfaces
demWriter.o: 	demWriter.c				demWriter.h 
# 	tool	compile flags	output name			files to compile
	gcc 	-c ${CCFLAGS}	-o demWriter.o		demWriter.c

# now with the error printer code
# target		implementation			interfaces
exitMessage.o:	exitMessage.c			exitMessage.h	
# 	tool	compile flags	output name	  		files to compile
	gcc		-c ${CCFLAGS}	-o exitMessage.o 	exitMessage.c  

# now with the dem cleaner code
# taget			implementation			interfaces
demCleaner.o:	demCleaner.c			demCleaner.h
# 	tool	compile flags	output name			files to compile
	gcc 	-c ${CCFLAGS}	-o demCleaner.o		demCleaner.c

# now with the module that writes to files
# target			implementation		interfaces
demWriteToFile.o: 	demWriteToFile.c	demWriteToFile.h
#	tool	compile flags	output name			files to compile
	gcc		-c ${CCFLAGS}	-o demWriteToFile.o	demWriteToFile.c

# now the module that programs use to read from files
# target			implementation		interfaces
demReadFromFile.o:	demReadFromFile.c	demReadFromFile.h	
# 	tool	compile flags	output name	  			files to compile
	gcc		-c ${CCFLAGS}	-o demReadFromFile.o 	demReadFromFile.c 

# now the module that checks ints
# target			implementation		interfaces
checkInt.o:			checkInt.c			checkInt.h
#	tool	compile flags	output name			files to compile
	gcc 	-c ${CCFLAGS}	-o checkInt.o		checkInt.c

# now the module that rounds numbers
# target			implementation 		interfaces
roundNumber.o:		roundNumber.c		roundNumber.h
#	tool	compile flags	output name			files to compile
	gcc 	-c ${CCFLAGS}   -o roundNumber.o	roundNumber.c

# now the module that sqrts numbers
# target			implementation 		interfaces
sqrtNumber.o:		sqrtNumber.c		sqrtNumber.h
#	tool 	compile flags 	output name 		files to compile	
	gcc		-c ${CCFLAGS}	-o sqrtNumber.o		sqrtNumber.c

# now the module that reverses endianness
# target			implementation 		interfaces
endianReverser.o:	endianReverser.c	endianReverser.h
#	tool 	compile flags	output name			files to compile
	gcc		-c ${CCFLAGS}	-o endianReverser.o	endianReverser.c
