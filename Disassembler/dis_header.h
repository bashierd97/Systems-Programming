//============== CS 530 Project 2 ~ Disassembler Header 1 ============== 

//Project Creators: Bashier Dahman 
//Class Information: CS 530, Fall 2020
//Assignment Information: Project #2, Disassembler 
//Filename: dis_header.h

// including libraries I will be using
#include <iostream>
#include<string> 
#include <fstream>
#include <sstream>
#include <bits/stdc++.h> 
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

// struct for the symbol table
struct Symbol {
	string symbolVal;
	string value;
	char flag;
};
// struct for the literal table
struct Literal {
	string name;
  string literalVal;
	int length;
	string address;
};

// reference to *.obj and *.sym file
string objFile;
string symFile;

/// Vectors of the Symbol & Literal Structs ////
vector<Symbol> symbols;
vector<Literal> literals;
////////////////////////////////////////////////

// function to get the file extension from the cmd line args
string getFileExt(const string& s) {

   size_t i = s.rfind('.', s.length());
   if (i != string::npos) {
      // returns the extension (i.e ".obj")
      return("." + s.substr(i+1, s.length() - i));
   }
   return("");
} // getFileExt function

// function to get the file name without the extension
string getFileNoExt(const string& s) {    
    string fileNameWithoutExtension = s.substr(0, s.rfind("."));
    // returns the file name w/o extension (i.e "sample")
    return fileNameWithoutExtension;
} // getFileNoExt function

// function to open and read the files and save them as strings
string openFiles(string fileOp, string type, int argc) {
	string returnVar = "";
	if (argc > 1) {
		string file1 = fileOp;
		file1.append(type);
		ifstream objfile(file1.c_str());
		if (objfile.is_open() && objfile.good()) {
			string line = "";
			while (getline(objfile, line)) {
				returnVar.append(line);
				returnVar.append("\n");
			}
		}
		else {
			cout << "\nFailed to open file:" + file1 << endl;
      cerr << "\nPlease check the name & format of the files and confirm they coincide\n";
      // exit if files are incorrect
      exit(1);
		}
	}
	return returnVar;
} //openFiles function

// function to handle parsing the symbol file
void parseSymFile(string symTabFile, vector<Symbol> &symbols, vector<Literal> &literals){
    
    // stringstream class ssSymFile
    stringstream ssSymFile(symTabFile); 
    
    // string to hold the current value in the stringstream
    string curLine; 
    
    // booleans to tell whether we are on the lines for the symbol table or literal table
    bool symLines = false, litLines = false;
    // bool to check whether the lit table value has a name or not
    bool hasName = false;
    
    // variables I used as indexes in my vector of structs
    int symTokPointer = 0, litTokPointer = 0;
       
    // Tokenizing the stream and getting every line in the symTabFile
    while(getline(ssSymFile, curLine))  {
         
        // if the cur line contains "Symbol" this means we're at the
        // header section of the sym table                        
        if (curLine.find("Symbol") != std::string::npos) {
            // then set the bool for sym lines to true
            // because we're only on the symbol table lines                    
            symLines = true;
            litLines = false;
            continue;
        }
        // if the cur line contains "Name" this means we're at the
        // header section of the lit table         
        else if (curLine.find("Name") != std::string::npos)  {
            // set the value of literal lines
            // to true and symbol lines to false, as we moved from those            
            litLines = true;
            symLines = false;
            continue;
        }
        // skip the dashes anytime they are found                
        else if ((curLine.find("------") != std::string::npos) || curLine.empty())
            continue;
       // this section is only for the symbol table lines
        if (symLines == true) {
                        
            // push back our struct data into the vector
            // hence 'vector of structs'                        
            symbols.push_back(Symbol());
            
            // sstream for the symbol table            
            stringstream ssSymTab(curLine);
            // value for current string
            string curVal;
            
            // variable to be a pointer in the symbol table values
            // anytime across any non white space value
            int valPointer = 0;

            // loop to iterate through the current line
            while (getline(ssSymTab, curVal, ' '))   {
                
                // ignore whitespace
                if (curVal == " " || curVal == "")
                    continue;

                // switch statement to iterate through the current 
                // NON-WHITESPACE values in the line
                switch (valPointer)  {      
                  // first value is the symbol          
                  case 0:
                      symbols[symTokPointer].symbolVal = curVal;
                      break;
                  // 2nd is the value
                  case 1:
                      symbols[symTokPointer].value = curVal;
                      break;
                  // 3rd is the flag 
                  case 2:
                      symbols[symTokPointer].flag = curVal[0];
                      break;
                }
                // continously iterate till we hit the end of the line
                valPointer++;
            }
            // point to the next line token
            symTokPointer++;
        }
        
        // if we detected that we were at the literal table
        // start parsing it's respective data
        else if (litLines == true)  {
            // push back our struct data into the vector
            // hence 'vector of structs' 
            literals.push_back(Literal());
            
            // sstream for the literal table   
            stringstream ssLitTab(curLine);
            // value for current string 
            string curVal;
            // variable to be a pointer in the symbol table values
            // anytime across any non white space value
            int valPointer = 0;
            
            // this section is to check if the literal has a name //
            // essentially we try to find the first char of the line
            // that's not equal to =
            string::size_type ch = curLine.find_first_not_of('=');
            // if the first char of the line is a white space,
            // then we know that literal has NO name
            if (curLine[ch] == ' ')
                hasName = false;
            // if the first char is not a white space
            // we know that means that lit has a name
            else if (curLine[ch] != ' ')
                 hasName = true;
            // loop to iterate through the current line
            while (getline(ssLitTab, curVal, ' '))   {

                // ignore whitespace
                if (curVal == "" || curVal == " ")
                    continue;
                // if the literal has no name, set the name as blank
                // and iterate through the rest of the strings to get the other values
                if(hasName == false) { 
                  // iterate through all non whitespace values in line
                  switch (valPointer)   {
                    case 0:
                        literals[litTokPointer].name = "";
                        literals[litTokPointer].literalVal = curVal;
                        break;
                    case 1:
                        literals[litTokPointer].length = atoi(curVal.c_str());
                        break;
                    case 2:
                        literals[litTokPointer].address = curVal;
                        break;
                  }
                }
                // if the literal has a name, this means we know have
                // 4 pointers for strings in the cur line
                else if (hasName == true) {
                  switch (valPointer)   {               
                  case 0:
                      // with the first value being the name of the literal
                      literals[litTokPointer].name = curVal;
                      break;
                  case 1:
                      // second being literal value  
                      literals[litTokPointer].literalVal = curVal;
                      break;
                  case 2:
                      // third being length
                      literals[litTokPointer].length = atoi(curVal.c_str());
                      break;
                  case 3:
                      // 4th being address
                      literals[litTokPointer].address = curVal;
                      break;                
                  }

                }
                // continously iterate till we hit the end of the line
                valPointer++;
            }
            
            // point to the next line token
            litTokPointer++;
        }
             
    }
    
} // parseSymFile function

// this function is used to output the reserved memory 
void reservedMem(vector<Symbol> &symbols,int address,int endAddress,ofstream &sicFile,ofstream &lisFile){
    
    // iterate thru the symbols struct
    for(int j = 1; j < symbols.size() ; j++) {
        char flag[2] = {symbols[j].flag, '\0'};
        // check if the symbol address is after the instruction addresses
        if(address <= strtol(symbols[j].value.c_str(),0,16)) {
            // check if the flag is a relative symbol
            if (strcmp(&flag[0], "R") == 0){
                // print the addresses in listing file
                lisFile << setw(4) << setfill('0') << uppercase << hex << right << strtol(symbols[j].value.c_str(),0,16) << "  ";
                // print the symbol values in .lis and .sic files
                lisFile << setw(9) << setfill(' ') << left << symbols[j].symbolVal;
                sicFile << setw(9) << setfill(' ') << left << symbols[j].symbolVal;

                // check if we're at the last symbol
                if (j == symbols.size() - 1){
                    // calculate the difference between the current address and the end address of 
                    // instructions
                    int difference =  endAddress - strtol(symbols[j].value.c_str(),0,16);
                    // check to see if difference is the size of word or byte
                    if (difference % 3 == 0){
                           lisFile << setw(8) << setfill(' ') << "RESW";
                           sicFile << setw(8) << setfill(' ') << "RESW";
                           lisFile << setw(10) << setfill(' ') << dec << (difference / 3) << endl;
                           sicFile << setw(10) << setfill(' ') << dec << (difference / 3) << endl;
                           lisFile << setw(15) << setfill(' ') << " ";
                           sicFile << setw(9) << setfill(' ') << " ";
                           lisFile << setw(8) << setfill(' ') << "END";
                           sicFile << setw(8) << setfill(' ') << "END";
                           lisFile << symbols[0].symbolVal << endl;
                           sicFile << symbols[0].symbolVal << endl;
                   } else {
                           lisFile << setw(8) << setfill(' ') << "RESB";
                           sicFile << setw(8) << setfill(' ') << "RESB";
                           lisFile << setw(10) << setfill(' ') << dec << difference << endl;
                           sicFile << setw(10) << setfill(' ') << dec << difference << endl;
                           lisFile << setw(15) << setfill(' ') << " ";
                           sicFile << setw(9) << setfill(' ') << " ";
                           lisFile << setw(8) << setfill(' ') << "END";
                           sicFile << setw(8) << setfill(' ') << "END";
                           lisFile << symbols[0].symbolVal << endl;
                           sicFile << symbols[0].symbolVal << endl;
                   }
                // else, read the last symbol
                } else {

                    // calculate difference of next address to current address
                    int difference = strtol(symbols[j+1].value.c_str(),0,16) - strtol(symbols[j].value.c_str(),0,16);

                    // check to see if difference is the size of word or byte
                    if (difference % 3 == 0){
                           lisFile << setw(8) << setfill(' ') << "RESW";
                           sicFile << setw(8) << setfill(' ') << "RESW";
                           lisFile << setw(10) << setfill(' ') << dec << (difference / 3) << endl;
                           sicFile << setw(10) << setfill(' ') << dec << (difference / 3) << endl;
                    } else {
                           lisFile << setw(8) << setfill(' ') << "RESB";
                           sicFile << setw(8) << setfill(' ') << "RESB";
                           lisFile << setw(10) << setfill(' ') << dec << difference << endl;
                           sicFile << setw(10) << setfill(' ') << dec << difference << endl;
                    }
                }
            }
        }
    }

} // reservedMem function
