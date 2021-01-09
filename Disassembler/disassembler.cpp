//============== CS 530 Project 2 ~ Disassembler Main ============== 

//Project Creators: Bashier Dahman 
//Class Information: CS 530, Fall 2020
//Assignment Information: Project #2, Disassembler 
//Filename: disassembler.cpp


// include the header files
#include "dis_header.h"
#include "helper_driver.h"

// main function
int main(int argc, char* argv[]) {
  
  // create a result instance of memory addresses class
  MemoryAddresses result; 
  
  // this section checks whether the correct input is being passed in //
  // the program will only run if there are 2 files with the same name
  if (argc != 2) {
    cout << "\nIncorrect Number of Paramaters - Please ReRun in the Following Format:\n";
    cout << "\n'dis (filename)'\n";
    cerr << "\nNO EXTENSION IS NEEDED FOR THE FILE NAME. (i.e: 'dis sample')\n"; 
    // exit gracefully, but failed program
    return 1;
  }
  else if (argc == 2) {
    // get name of file (no extension)
    objFile = getFileNoExt(argv[1]);
    symFile = getFileNoExt(argv[1]);
    string objFileString = openFiles(objFile, ".obj", 2);
    string symFileString = openFiles(symFile, ".sym", 2);
    // parse the symbol file
    parseSymFile(symFileString, symbols, literals);
    
    // output .sic and .lis files
    ofstream sicFile, lisFile;
    
    // strings to hold names of 
    string newSicFile, newListFile;
    
    // append the new file extensions to the strings
    newSicFile.append(symFile);
    newSicFile.append(".sic");
    newListFile.append(symFile);
    newListFile.append(".lis");
    
    // open .sic file to output things inside
    sicFile.open(newSicFile.c_str());
    
    // open .lis file
    lisFile.open(newListFile.c_str());
  
    // store the returned class object into the new class object
    result = parseObjFile(objFileString, symbols, literals, sicFile, lisFile);
    
    reservedMem(symbols, result.memAddress, result.endMemAddress, sicFile, lisFile);
  
    // close output files
    sicFile.close();
    lisFile.close();
    
    return 0; // exit successfully

  } // if statement
  
} // main