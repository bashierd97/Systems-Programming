//============== CS 530 Project 2 ~ Disassembler Header 2 ============== 

//Project Creators: Bashier Dahman 
//Class Information: CS 530, Fall 2020
//Assignment Information: Project #2, Disassembler 
//Filename: helper_driver.h

// including libraries I will be using
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <map>

using namespace std;

// class to reference the addresses
class MemoryAddresses {
  public:
    int memAddress, endMemAddress;
};

// variables
bool noName = false; // used to detect if symbol has a name
string label = ""; // used for labelling an address
int objFilePointer; // pointer to reference where we are in obj file
bool overboard = false; // bool to check if we go over
bool n,i,x,b,p,e = false; // booleans to know which flags are set
string operand = ""; // used for operands
bool opLabel = false; // boolean for operand - label
string baseRegister = ""; // used for the base register
bool lit = false; // boolean for literal operand
bool LTORG = false; // boolean for LTORG
bool firstLit = true; // boolean for first literal
bool characters = false; // boolean to check flag for 2+ char's
bool baseWasPrinted = false; // bool to check if base was printed
bool bRegisterLoaded = false; // bool to check if base register is loaded


// function to handle parsing the object file
MemoryAddresses parseObjFile(string objFile, vector<Symbol> &symbols, vector<Literal> &literals, ofstream &sicFile, ofstream &listFile) {
  
  // create instance of class
  MemoryAddresses ma;

  // using a map to reference the instructions
  map<int, string> instruction_map;
  // insert all values opcodes & their respective values into map
  instruction_map.insert(make_pair(0x18,"ADD3"));
  instruction_map.insert(make_pair(0x58,"ADDF3"));
  instruction_map.insert(make_pair(0x90,"ADDR2"));
  instruction_map.insert(make_pair(0x40,"AND3"));
  instruction_map.insert(make_pair(0xB4,"CLEAR2"));
  instruction_map.insert(make_pair(0x28,"COMP3"));    
  instruction_map.insert(make_pair(0x88,"COMPF3"));
  instruction_map.insert(make_pair(0xA0,"COMPR2"));
  instruction_map.insert(make_pair(0x24,"DIV3"));
  instruction_map.insert(make_pair(0x64,"DIVF3"));
  instruction_map.insert(make_pair(0x9C,"DIVR2"));
  instruction_map.insert(make_pair(0xC4,"FIX1"));
  instruction_map.insert(make_pair(0xC0,"FLOAT1"));
  instruction_map.insert(make_pair(0xF4,"HIO1"));
  instruction_map.insert(make_pair(0x3C,"J3"));
  instruction_map.insert(make_pair(0x30,"JEQ3"));
  instruction_map.insert(make_pair(0x34,"JGT3"));
  instruction_map.insert(make_pair(0x38,"JLT3"));
  instruction_map.insert(make_pair(0x48,"JSUB3"));
  instruction_map.insert(make_pair(0x00,"LDA3"));
  instruction_map.insert(make_pair(0x68,"LDB3"));
  instruction_map.insert(make_pair(0x50,"LDCH3"));
  instruction_map.insert(make_pair(0x70,"LDF3"));
  instruction_map.insert(make_pair(0x8,"LDL3"));
  instruction_map.insert(make_pair(0x6C,"LDS3"));
  instruction_map.insert(make_pair(0x74,"LDT3"));
  instruction_map.insert(make_pair(0x04,"LDX3"));
  instruction_map.insert(make_pair(0xD0,"LPS3"));
  instruction_map.insert(make_pair(0x20,"MUL3"));
  instruction_map.insert(make_pair(0x60,"MULF3"));
  instruction_map.insert(make_pair(0x98,"MULR2"));
  instruction_map.insert(make_pair(0xC8,"NORM1"));
  instruction_map.insert(make_pair(0x44,"OR3"));
  instruction_map.insert(make_pair(0xD8,"RD3"));
  instruction_map.insert(make_pair(0xAC,"RMO2"));
  instruction_map.insert(make_pair(0x4C,"RSUB3"));
  instruction_map.insert(make_pair(0xA4,"SHIFTL2"));
  instruction_map.insert(make_pair(0xA8,"SHIFTR2"));
  instruction_map.insert(make_pair(0xF0,"SIO1"));
  instruction_map.insert(make_pair(0xEC,"SSK3"));
  instruction_map.insert(make_pair(0x0C,"STA3"));
  instruction_map.insert(make_pair(0x78,"STB3"));
  instruction_map.insert(make_pair(0x54,"STCH3"));
  instruction_map.insert(make_pair(0x80,"STF3"));
  instruction_map.insert(make_pair(0xD4,"STI3"));
  instruction_map.insert(make_pair(0x14,"STL3"));
  instruction_map.insert(make_pair(0x7C,"STS3"));
  instruction_map.insert(make_pair(0xE8,"STSW3"));
  instruction_map.insert(make_pair(0x84,"STT3"));
  instruction_map.insert(make_pair(0x10,"STX3"));
  instruction_map.insert(make_pair(0x1C,"SUB3"));
  instruction_map.insert(make_pair(0x5C,"SUBF3"));
  instruction_map.insert(make_pair(0x94,"SUBR2"));
  instruction_map.insert(make_pair(0xB0,"SVC2"));
  instruction_map.insert(make_pair(0xE0,"TD3"));
  instruction_map.insert(make_pair(0xF8,"TIO1"));
  instruction_map.insert(make_pair(0x2C,"TIX3"));
  instruction_map.insert(make_pair(0xB8,"TIXR2"));
  instruction_map.insert(make_pair(0xDC,"WD3"));    
  
  // variable to keep track of addresses
  ma.memAddress = 0;
  
  // stringstream class ssSymFile
  // use the stream to parse the values inside the object file
  stringstream ssObjFile(objFile); 
  
  // string to hold the current value in the stringstream
  string curLine; 
  
  // Create a 'while' loop that iterates per line in record file.
  while(getline(ssObjFile, curLine))  {
      // set pointer to 0
      objFilePointer = 0;
      // another string of the current line, this is needed for substrings
      string line(curLine);
      // check if first char in line indicates header record
      if(curLine[0] == 'H') {
          // if it's a header record retrieve the substring indicating program name
          string programName = line.substr(1,6);
          // increment past program name
          objFilePointer += 7;
          // retrieve starting address of line & convert to hex
          ma.memAddress = strtol(line.substr(objFilePointer,6).c_str(), 0, 16);
          // this is used to retrieve the ending address 
          ma.endMemAddress = strtol(curLine.substr(13,6).c_str(), 0, 16);

          // output first line of program to both sic & lis files
          listFile << setw(4) << setfill('0') << uppercase << hex << ma.memAddress << "  ";
          listFile << setw(8) << setfill(' ') << left << programName;
          sicFile << setw(8) << setfill(' ') << left << programName;
          listFile << " START   " << uppercase << ma.memAddress << endl;
          sicFile << " START   " << uppercase << ma.memAddress << endl;
      }
      // check if first char in line indicates text record
      if(curLine[0] == 'T') {
          // retrieve starting address of line & convert to hex
          ma.memAddress = strtol(line.substr(1,6).c_str(), 0, 16);
          // move pointer up 9 nibbles
          objFilePointer+=9;
          // continue to read text record until new line
          while(curLine[objFilePointer] != '\n') {
              if (overboard) break;              
                      opLabel = false; 
                      firstLit = true; // indicate we're on first literal
                      // set n i x b bits to false 
                      n = false;
                      i = false;
                      x = false;
                      b = false;
                      
                      // iterate thru size of symbol struct to see if symbol address
                      // matches memAddress, if it does set label to the symbol value
                      // at that address
                      for(int j = 0; j < symbols.size(); j++) {
                          if(strtol(symbols[j].value.c_str(),0,16) == ma.memAddress) {
                              label = symbols[j].symbolVal; 
                          }
                      }
                      // for loop to iteratet thru size of literal struct
                      // retrieving the type of literal and actual literal
                      for(int m=0; m < literals.size(); m++){
                          int actualLiteral = 0;
                          int possibleLiteral = 0;
                          int val = 0;
                          // retrieve literal type 
                          string literalType = literals[m].literalVal.substr(1,1);
                          // retrieve literal
                          string literal = literals[m].literalVal.substr(3,literals[m].length);

                          // verify what type of literal the var is
                          if (strcmp (&literalType[0], "X") == 0){
                              // set the actual literal 
                              actualLiteral = strtol(literal.c_str(), 0, 16);
                              // check if going over the length of the line
                              if (line.size() > objFilePointer + (2 * strtol(literals[m].address.c_str(),0,16)) + literals[m].length + 2){
                                  // set possible literal
                                  possibleLiteral = strtol(line.substr(objFilePointer + (2 * strtol(literals[m].address.c_str(),0,16)), literals[m].length).c_str(), 0, 16);
                              }
                          }
                          // check if literal type is D 
                          else if (strcmp (&literalType[0], "D") == 0){
                              // if it is set the actual literal
                              actualLiteral = strtol(literal.c_str(), 0, 10);
                              if (line.size() > objFilePointer + (2 * strtol(literals[m].address.c_str(),0,16)) + literals[m].length + 2){
                                  possibleLiteral = strtol(line.substr(objFilePointer + (2 * strtol(literals[m].address.c_str(),0,16)), literals[m].length).c_str(), 0, 16);
                              }
                          } else {
                              actualLiteral = 0;
                              for (int l=0; l < literal.size(); l++){
                                  actualLiteral *= 256;
                                  actualLiteral += literal[l];
                              }
                              if (line.size() > objFilePointer + (2 * strtol(literals[m].address.c_str(),0,16)) + (2 * literals[m].length) + 2){
                                  possibleLiteral = strtol(line.substr(objFilePointer + (2 * strtol(literals[m].address.c_str(),0,16)), (2 * literals[m].length)).c_str(), 0, 16);
                              }
                          }
                          
                          // if the first literal is found, print LTORG
                          if (possibleLiteral == actualLiteral && firstLit){
                              
                              listFile << setw(20) << setfill(' ') << right << "LTORG" << endl;
                              sicFile << setw(14) << setfill(' ') << right << "LTORG" << endl;
                              firstLit = false;
                              LTORG = true;
                          }
                          // check if any literals where found before current objFilePointer
                          if (LTORG){
                              string literal = literals[m].literalVal.substr(3,literals[m].length);
                              string literalType = literals[m].literalVal.substr(1,1);

                              // verify what type of literal the var is
                              if (strcmp (&literalType[0], "X") == 0){
                                  actualLiteral = strtol(literal.c_str(), 0, 16);
                                  if (line.size() > objFilePointer + literals[m].length + 2){
                                      possibleLiteral = strtol(line.substr(objFilePointer, literals[m].length).c_str(), 0, 16);
                                  }
                              } else if (strcmp (&literalType[0], "D") == 0){
                                  actualLiteral = strtol(literal.c_str(), 0, 10);
                                  if (line.size() > objFilePointer + literals[m].length + 2){
                                      possibleLiteral = strtol(line.substr(objFilePointer, literals[m].length).c_str(), 0, 16);
                                  }
                              } else {
                                  actualLiteral = 0;
                                  // convert the actual ascii literal into int
                                  for (int j=0; j < literal.size(); j++){
                                      actualLiteral *= 256;
                                      actualLiteral += literal[j];
                                  }
                                  // Create an 'if' statement to check for the literal after the line.
                                  if (line.size() > objFilePointer + (2 * literals[m].length) + 2){
                                      possibleLiteral = strtol(line.substr(objFilePointer, (2 * literals[m].length)).c_str(), 0, 16);
                                  }
                                  characters = true;
                              }
                              // check if the current possible literal equals to the actual literal
                              // if so output it to the files
                              if (possibleLiteral == actualLiteral){

                                  listFile << setw(4) << setfill('0') <<
                                  uppercase << hex << right << ma.memAddress << "  ";
                                  
                                  // Check if the literal has a name and print it.
                                  if (literals[m].name[0] == '\0'){
                                      noName = true;
                                      listFile << setw(10) << setfill(' ') << "*";
                                  } else {
                                      listFile << setw(8) << setfill(' ') << left << literals[m].name;
                                  }
                                  
                                  if(noName) {
                                    listFile << setw(12) << setfill(' ') << literals[m].literalVal;
                                    listFile << setw(7) << setfill(' ') << literal << endl;
                                  } else {
                                    listFile << setw(19) << setfill(' ') << left << literals[m].literalVal;
                                    listFile << setw(10) << setfill(' ') << left << literal << endl;
                                  }

                                  // Create an 'if/else' if the literal is a character,
                                  // then position in the line and address address variables differently.
                                  if (characters) {
                                      objFilePointer += literals[m].length * 2;
                                      ma.memAddress += literals[m].length;
                                      characters = false;
                                  } else {
                                      objFilePointer += literals[m].length;
                                      ma.memAddress += (literals[m].length / 2);
                                  }
                              }
                          }
                      }
              if (objFilePointer + 2 > line.size()) {
                  overboard = true;
                  continue;
              }

              int opCode = strtol(line.substr(objFilePointer,2).c_str(), 0, 16);

              string fullObjCode;

              // Create an int variable that will find what the n and i bits are set to.
              int remainder = opCode % 4;

              // Set the opCode to the actual opCode
              opCode = opCode - remainder;

              // Separat the instruction name from format type
              string instructionAndFormat = instruction_map[opCode];
              string instruction = instructionAndFormat.substr(0,instructionAndFormat.size()-1);
              int format = instructionAndFormat[instructionAndFormat.size()-1] - '0';
              
              
              // Create 'if/else' statement to verify format.
              // If the remainder isn't 0. It is a format 3 or 4 instruction
              if(remainder == 3) {
                  n = true;
                  i = true;
              } else if(remainder == 2) {
                  n = true;
                  i = false;
              } else if(remainder == 1) {
                  n = false;
                  i = true;
              } else {
                  n = false;
                  i = false;
              }
              // Create 'if else' statements to determine each format.
              if(format == 1) {

                  // Print the address
                  listFile << setw(4) << setfill('0') << uppercase << hex << right << ma.memAddress << "  ";

                  // Print the label if there is one given the address
                  listFile << setw(8) << setfill(' ') << left << label;
                  sicFile << setw(8) << setfill(' ') << left << label;

                  // Used to get 1 byte, the OpCode.
                  fullObjCode = line.substr(objFilePointer,2);
                  objFilePointer+=2;
                  listFile << " ";
                  sicFile << " ";
                  listFile << setw(17) << setfill(' ') << left << instruction;
                  sicFile << setw(17) << setfill(' ') << left << instruction;
                  ma.memAddress+=1;

              } else if(format == 2) {
                  if (objFilePointer + 4 > line.size()) {
                      overboard = true;
                      continue;
                  }
                  // Print the address
                  listFile << setw(4) << setfill('0') << uppercase << hex << right << ma.memAddress << "  ";

                  // Print the label if there is one given the address
                  listFile << setw(8) << setfill(' ') << left << label;
                  sicFile << setw(8) << setfill(' ') << left << label;

                  // output instructions to files
                  listFile << " ";
                  sicFile << " ";
                  listFile << setw(8) << setfill(' ') << left << instruction;
                  sicFile << setw(8) << setfill(' ') << left << instruction;
                  fullObjCode = line.substr(objFilePointer,4); //Gets 2 bytes

                  // Used to 'register' the arithmetic to match numbers to letters
                  int reg1 = strtol(fullObjCode.substr(2,1).c_str(), 0, 10);
                  int reg2 = strtol(fullObjCode.substr(3,1).c_str(), 0, 10);
                  char register1;
                  char register2;
                  char reg = reg1;
                  char registrar;
                  for (int i=0; i<2; i++){
                    if(reg == 0) {
                      registrar = 'A';
                    } 
                    else if (reg == 1) {
                      registrar = 'X';
                    } 
                    else if (reg == 2) {
                      registrar = 'L';
                    } 
                    else if (reg == 3) {
                      registrar = 'B';
                    } 
                    else if (reg == 4) {
                      registrar = 'S';
                    } 
                    else if (reg == 5) {
                      registrar = 'T';
                    } 
                    else if (reg == 6) {
                      registrar = 'F';
                    } 
                    else if (reg == 8) {
                      registrar = '*';
                    } else {
                      registrar = ' ';
                    }           
                      reg = reg2;
                      if (i == 0){
                          register1 = registrar;
                          registrar = register2;
                      }
                      if (i == 1){
                          register2 = registrar;
                      }
                  }
                  
                  // Create 'if/else' statement to format the outputs based on their instructions
                  if ( opCode == 0xB4 || opCode == 0xB8 ){
                      listFile << setw(9) << setfill(' ') << left << register1;
                      sicFile << setw(9) << setfill(' ') << left << register1;
                  } else if ( opCode == 0xA4 || opCode == 0xA8 ){
                      listFile << register1 << "," << reg2 << "      ";
                      sicFile << register1 << "," << reg2 << "      ";
                  } else if ( opCode == 0xB0 ){
                      listFile << setw(9) << setfill(' ') << left << reg1;
                      sicFile << setw(9) << setfill(' ') << left << reg1;
                  } else {
                      listFile << register1 << "," << register2 << "      ";
                      sicFile << register1 << "," << register2 << "      ";
                  }
                  listFile << fullObjCode;
                  objFilePointer+=4;
                  ma.memAddress+=2;
              }
              // Create an 'else/if' statement to be used for both Format 3 & Format 4 that is in the opcode table.
              else if(format == 3) {

                  if (objFilePointer + 6 > line.size()) {
                      overboard = true;
                      continue;
                  }
                  int xbpeInt = strtol(line.substr(objFilePointer+2,1).c_str(), 0, 16);
                  int targetAddress = strtol(line.substr(objFilePointer+3,3).c_str(), 0, 16);

                  // Create an 'if' statement to check if the 'b' bit is set
                  if ((xbpeInt >= 4 && xbpeInt <= 7) || xbpeInt >= 12) {

                      // Use to assist printing the instruction.
                      b = true;

                      // Used if the b register was previously loaded using LDB,
                      // if so, then use the operand that was loaded to print the
                      // BASE assembly directive.
                      if (bRegisterLoaded){
                          
                          listFile << setw(23) << setfill(' ') << right << "BASE    " << uppercase << baseRegister << endl;
                          sicFile << setw(17) << setfill(' ') << right << "BASE    " << uppercase << baseRegister << endl;
                          operand = baseRegister;
                          
                          baseWasPrinted = true;
                      }
                  }

                  // Create an 'if' statement to check if p bit is set
                  if (xbpeInt == 2 || xbpeInt == 3 || xbpeInt == 6 || xbpeInt == 7 ||
                      xbpeInt == 10 || xbpeInt == 11 || xbpeInt == 14 || xbpeInt == 15){

                      // Used if set to base relative addressing and now have a PC relative
                      // addressing instruction, then specify NOBASE
                      if (baseWasPrinted) {
                          listFile << setw(23) << setfill(' ') << right << "NOBASE  " << uppercase << endl;
                          sicFile << "         NOBASE  " << uppercase << endl;
                          baseWasPrinted = false;
                      }
                  }

                  // Used to Print the address
                  listFile << setw(4) << setfill('0') << uppercase << hex << right << ma.memAddress << "  ";
                  
                  // Used to Print the label if there is one given the address
                  listFile << setw(8) << setfill(' ') << left << label;
                  sicFile << setw(8) << setfill(' ') << left << label;

                  ma.memAddress+=3;

                  // Create an 'if' statement to check if e bit is set, if it is not, then it is
                  // a format 3 instruction.
                  if (xbpeInt % 2 == 0) {

                      // This is used to get 3 bytes.
                      fullObjCode = line.substr(objFilePointer,6);

                      // Used to check if x bit is set
                      if (xbpeInt >= 8) x = true;

                      // Used to check if p bit is set
                      if (xbpeInt == 2 || xbpeInt == 3 || xbpeInt == 6 || xbpeInt == 7 ||
                          xbpeInt == 10 || xbpeInt == 11 || xbpeInt == 14 || xbpeInt == 15){
                          targetAddress += ma.memAddress;
                      }

                      // If the Targeting Address is 1XXX in hex, it was a backward reference
                      // and then only take the first three digits
                      if (targetAddress > 4096) targetAddress -= 4096;

                      // Used if there is something loaded into the b reg and we have a b flag
                      if (bRegisterLoaded && b){

                          // Used if using a baseRegister string
                          bRegisterLoaded = false;
                      } else {

                          // Otherwise use a 'for' loop to look for any possible operands.
                          for(int j = 1; j < symbols.size(); j++) {
                              if(strtol(symbols[j].value.c_str(),0,16) == targetAddress) {
                                  operand = symbols[j].symbolVal;
                                  opLabel = true;
                              }
                          }

                          int tmp = objFilePointer;
                          objFilePointer = (targetAddress * 2) + 9;

                          // Use a 'for' loop to verify if the target address is a literal
                          for(int n=0; n < literals.size(); n++){
                              string literalType = literals[n].literalVal.substr(1,1);
                              string literal = literals[n].literalVal.substr(3,literals[n].length);
                              lit = false;
                              int actualLiteral = 0;
                              int possibleLiteral = 0;
                              int val = 0;

                              // Create 'if/else' statements to verify the type of literal.
                              // First look ahead from the current address plus the address
                              // listed in the literal file
                              if (strcmp (&literalType[0], "X") == 0){
                                  actualLiteral = strtol(literal.c_str(), 0, 16);
                                  if (line.size() > objFilePointer + literals[n].length){
                                      possibleLiteral = strtol(line.substr(objFilePointer,
                                                               literals[n].length).c_str(), 0, 16);
                                  }
                              } else if (strcmp (&literalType[0], "D") == 0){
                                  actualLiteral = strtol(literal.c_str(), 0, 10);
                                  if (line.size() > objFilePointer + literals[n].length){
                                      possibleLiteral = strtol(line.substr(objFilePointer,
                                                               literals[n].length).c_str(), 0, 16);
                                  }
                              } else {
                                  actualLiteral = 0;
                                  for (int i=0; i < literal.size(); i++){
                                      actualLiteral *= 256;
                                      actualLiteral += literal[n];
                                  }
                                  if (line.size() > objFilePointer + (2 * literals[n].length)){
                                      possibleLiteral = strtol(line.substr(objFilePointer,
                                                               (2 * literals[n].length)).c_str(), 0, 16);
                                  }
                              }
                              
                              if (possibleLiteral == actualLiteral){
                                      operand = literals[n].literalVal;
                                      lit = true;
                                      break;
                              }
                          }
                          objFilePointer = tmp;
                      }
                      // increment pointer by 6 nibbles
                      objFilePointer += 6;
                      // output instruction to files
                      listFile << " ";
                      sicFile << " ";
                      listFile << setw(7) << setfill(' ') << left << instruction;
                      sicFile << setw(7) << setfill(' ') << left << instruction;
                      string format;
                      
                      // check which bits were set to determine the format of output
                      if (i && !n && !x && !b){
                          if (opLabel){
                              listFile << "#" << setw(9) << setfill(' ') << operand;
                              sicFile << "#" << setw(9) << setfill(' ') << operand;
                          } else {
                              listFile << "#" << setw(9) << setfill(' ') << targetAddress;
                              sicFile << "#" << setw(9) << setfill(' ') << targetAddress;
                          }
                      } else if (i && !n && !x && b){
                           listFile << "#" << setw(9) << setfill(' ') << baseRegister;
                           sicFile << "#" << setw(9) << setfill(' ') << baseRegister;
                      } else if (!i && n && !x && !b){
                           listFile << "@" << setw(9) << setfill(' ') << operand;
                           sicFile << "@" << setw(9) << setfill(' ') << operand;
                      } else if (!i && n && !x && b){
                           listFile << "@" << setw(9) << setfill(' ') << baseRegister;
                           sicFile << "@" << setw(9) << setfill(' ') << baseRegister;
                      } else if (!x && !b){
                           // If a literal was found at the target address, print.
                           if (lit){
                               listFile << setw(10) << setfill(' ') << operand;
                               sicFile << setw(10) << setfill(' ') << operand;
                           } else {
                               listFile << " ";
                               sicFile << " ";
                               listFile << setw(9) << setfill(' ') << operand;
                               sicFile << setw(9) << setfill(' ') << operand;
                           }
                      } else if (!x && b){
                           if (lit){
                               listFile << setw(10) << setfill(' ') << operand;
                               sicFile << setw(10) << setfill(' ') << operand;
                           } else {
                               listFile << " ";
                               sicFile << " ";
                               listFile << setw(9) << setfill(' ') << baseRegister;
                               sicFile << setw(9) << setfill(' ') << baseRegister;
                          }
                      } else if (x && !b){
                           listFile << " ";
                           sicFile << " ";
                           format = operand + ",X";
                           listFile << setw(9) << setfill(' ') << format;
                           sicFile << setw(9) << setfill(' ') << format;
                      } else if (x && b){
                           listFile << " ";
                           sicFile << " ";
                           format = baseRegister + ",X";
                           listFile << setw(9) << setfill(' ') << format;
                           sicFile << setw(9) << setfill(' ') << format;
                      }
                      listFile << " ";
                      sicFile << " ";
                      listFile << fullObjCode;
                  } else {   // this means format 4 instruction       
                      if (objFilePointer + 8 > line.size()) {
                          overboard = true;
                          continue;
                      }
                      int targetAddress4 = strtol(line.substr(objFilePointer+3,5).c_str(), 0, 16);

                      // Used to find the label for operand field
                      operand = "";
                      for(int j = 1; j < symbols.size() ; j++) {
                          if(strtol(symbols[j].value.c_str(),0,16) == targetAddress4) {
                              operand = symbols[j].symbolVal;
                          }
                      }
                      int tmp = objFilePointer;
                      objFilePointer = (targetAddress4 * 2) + 9;

                      // loop thru literal struct size if target address is literal
                      for(int z=0; z < literals.size(); z++){
                          string literalType = literals[z].literalVal.substr(1,1);
                          string literal = literals[z].literalVal.substr(3,literals[z].length);
                          lit = false;
                          int actualLiteral = 0;
                          int possibleLiteral = 0;
                          int val = 0;

                          // Create 'if/else' to verify what type of literal it is
                          // If so, look ahead from the current address plus the address
                          // listed in the literal file.
                          if (strcmp (&literalType[0], "X") == 0){
                              actualLiteral = strtol(literal.c_str(), 0, 16);
                              if (line.size() > objFilePointer + literals[z].length + 1){
                                  possibleLiteral = strtol(line.substr(objFilePointer,
                                                           literals[z].length).c_str(), 0, 16);
                              }
                          } else if (strcmp (&literalType[0], "D") == 0){
                              actualLiteral = strtol(literal.c_str(), 0, 10);
                              if (line.size() > objFilePointer + literals[z].length + 1){
                                  possibleLiteral = strtol(line.substr(objFilePointer,
                                                           literals[z].length).c_str(), 0, 16);
                              }
                          } else {
                              actualLiteral = 0;
                              for (int i=0; i < literal.size(); i++){
                                  actualLiteral *= 256;
                                  actualLiteral += literal[z];
                              }
                              if (line.size() > objFilePointer + (2 * literals[z].length) + 1){
                                  possibleLiteral = strtol(line.substr(objFilePointer,
                                                           (2 * literals[z].length)).c_str(), 0, 16);
                              }
                          }

                          if (possibleLiteral == actualLiteral){
                                  operand = literals[z].literalVal;
                                  lit = true;
                                  break;
                          }
                      }
                      objFilePointer = tmp;
                      // retrieve the 4 bytes
                      fullObjCode = line.substr(objFilePointer,8);
                      // increment objFilePointer
                      objFilePointer += 8;
                      ma.memAddress += 1;
                      listFile << "+";
                      sicFile << "+";
                      listFile << setw(7) << setfill(' ') << left << instruction;
                      sicFile << setw(7) << setfill(' ') << left << instruction;

                      if (i && !n){
                           listFile << "#" << setw(10) << setfill(' ') << operand;
                           sicFile << "#" << setw(10) << setfill(' ') << operand;
                      } else if (!i && n){
                           listFile << "@" << setw(10) << setfill(' ') << operand;
                           sicFile << "@" << setw(10) << setfill(' ') << operand;
                      } else {
                          if (!lit){
                              listFile << " ";
                              sicFile << " ";
                          }
                          listFile << setw(10) << setfill(' ') << operand;
                          sicFile << setw(10) << setfill(' ') << operand;
                      }

                      // output object code
                      listFile << fullObjCode;
                  }

                  // If LDB was used, annotate the operand.
                  if (opCode == 0x68){
                      baseRegister = operand;
                      bRegisterLoaded = true;
                  }
                  label = "";
                  operand = "";
                  listFile << endl;
                  sicFile << endl;
              }
          }
    }
  }
  return ma; // return class object
} // parseObjFile function