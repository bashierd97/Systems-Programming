#============== CS 530 Project 2 ~ MakeFile ============== 

#Project Creators: Bashier Dahman
#Class Information: CS 530, Fall 2020
#Assignment Information: Project #2, Disassembler
#Filename: makefile

################################################################
#          Make File: To Compile Project 2 Assignment          #
#                      Bashier Dahman                          #  
################################################################

# defining our compiler
CC	=	g++

# running g++ and creating the executable file / then running it
all:

	@echo	"Compiling disassembler.cpp"

	$(CC)	-o	dis	disassembler.cpp
	
# this will remove the dis file to clean up the dir.
clean:
	@echo "Now removing 'dis' executable & any .sic / .lis files"

	rm	dis	*.sic	*.lis
#######################[ EOF: Makefile ]###################
