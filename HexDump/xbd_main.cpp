//============== CS 530 Project 1 ~ Main File ============== 

//Project Creators: Bashier Dahman
//Class Information: CS 530, Fall 2020
//Assignment Information: Project #1, HexDump 
//Filename: xbd_main.cpp

// include my header file
#include "xbd_header.h"

// main function
int main ( int argc, char *argv[] ) {
  
  // flag variable we will be using to determine
  // whether binary output will be shown
  string flag = "-b";
  
  // check if there's proper amount of arguments
  if ( argc < 2 || argc > 3 ) {
    cout<<"ERROR: PLEASE INPUT THE CORRECT AMOUNT OF PARAMETERS\n";
    exit(0); // exit if incorrect amount of parameters
    
  } else {
    // if the -b flag is passed in do the binary output
    if(argv[1] == flag) { 
        // pass in file as argument to function
        char *in_file = argv[2];
        do_binary(in_file);
    } // end if statement     
        
    // anything else means to just do the hex output
    else {
      // pass in file as argument to function
      char *in_file = argv[1];
      do_hex(in_file);
    }
        
  } // end main else statement
  
  // return 0 to indicate successful program completion
  return 0;
  
} // main
  