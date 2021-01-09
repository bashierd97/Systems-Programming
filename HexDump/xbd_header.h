//============== CS 530 Project 1 ~ Header File ============== 

//Project Creators: Bashier Dahman
//Class Information: CS 530, Fall 2020
//Assignment Information: Project #1, HexDump 
//Filename: xbd_header.h

// all the lib's I will be utilizing
#include <stdio.h> 
#include <stdlib.h> 
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctype.h>
#include <cstring>
#include <cstdlib>
#include <bits/stdc++.h> 

using namespace std;

// function to preform the binary output 
void do_binary(char *argv){

      // all the variables I will be using
      FILE* input;  // input file passed in 

      int c; // variable that will be used to read thru file
      int byte_count = 0; // to help count number of hex bytes per line
      int addressline = 0; // to help insert address in beginning of line
      int addresscount = 0; // to calculate actual address
      char output_char[6]; // creating a char array to output the hex values as ASCII
      int i = 0; // iterating variable to iterate thru char array
      int count_char = 0; // variable used to count # of char's in line  
      
      char hex_string[20]; // will be used to help convert hex to binary
      
      // open file passed in
      input = fopen(argv, "r");
      
      // this will handle any invalid file passed in
      if (input == NULL) {
        // output error message
        cout << "No such file exists!" << endl;
        exit(1); // exit
      }
      
      // read through file as long as its not end of file
      while((c = fgetc(input)) != EOF){   
      
      // insert address in beginning of line
        if(addressline == 0) {
          // display address 
          printf("%07x: ", addresscount);
        }
        // increment addressline variable
        addressline++;
        
        // insert hex value into char array
        output_char[i] = c;
        // increment my i value
        i++; 
        count_char += 8; // because the binary value is 8 char's long increment by 8
          
        //this part is used to get binary of hex values//
        sprintf(hex_string, "%x", c); //insert hex value in array of char
        string s = hex_string; // set string s to hex_string
        stringstream ss;
        ss << hex << s;
        unsigned n;
        ss >> n;
        // use bitset to convert hex value to binary
        bitset<8> b(n);
        /////////////////////////////////////////////////
        
        
        // output binary value
        cout << b.to_string() << " ";
        // increment my count char variable due to the extra space
        count_char++;
        
        
          // for hex output split lines every 16 values
        if (byte_count == 5) {
            printf(" "); // to make it more like "xxd" insert another space
            // iterate through hex values and display if it's a valid ASCII char.
            for (int j = 0; j < 6; j++) { 
              if(isprint(output_char[j]))
                  printf("%c", output_char[j]); // valid ascii
               else
                  printf("."); // if not valid, print "."
            }          
            printf("\n"); // insert a new line
            byte_count = 0; // reset byte_count
            addresscount += 6; // add value to address
            addressline = 0; // reset address line
            i = 0; // reset iterating variable to reinsert values in char array
            count_char = 0; // reset counting chars for that line
        } else {
            byte_count += 1; // continue until we get 5
        }
                
      } // end while [reading file]
    
      // this part calculates the final line, if it contains less than 6 binary values
      
      // 54 is the number of chars (not including address and its respective
      // space) leading up to ascii output
      int num_space = 54 - count_char; // subtract 54 with num of chars in line
      
      // insert that many spaces so it aligns with rest of columns
      for (int z = 0; z < num_space; z++) {
          printf(" ");
      }
      // print one more to align with xxd
      printf(" ");
      // output valid ascii characters again 
      for (int j = 0; j < i; j++){
        if(isprint(output_char[j])) {
            printf("%c", output_char[j]);
        } else {
            printf("."); // invalid ascii char
        }
      }
      
      // insert new line so output looks nice
      cout << endl;
      // close file successfully
      fclose(input);
      
} // end of do_binary function

/////////////////////////////////////////////////////////////////////////////////////////////

// function to perform the hex output
void do_hex(char *argv) {
      // all the variables I will be using
      FILE* input;  // input file passed in 
  
      int spaceCount =0; // to help count and insert spaces
      int c; // variable that will be used to read thru file
      int byte_count = 0; // to help count number of hex bytes per line
      int addressline = 0; // to help insert address in beginning of line
      int addresscount = 0; // to calculate actual address
      char output_char[16]; // creating a char array to output the hex values as ASCII
      int i = 0; // iterating variable to iterate thru char array
      int count_char = 0; // variable used to count # of char's in line
      
      // open file passed in
      input = fopen(argv, "r");
      
      // this will handle any invalid file passed in
      if (input == NULL) {
        // output error message
        cout << "No such file exists!" << endl;
        exit(1); // exit
      }
      
      // read through file as long as its not end of file
      while((c = fgetc(input)) != EOF){
        
        // insert address in beginning of line
        if(addressline == 0) {
          // display address 
          printf("%06x0: ", addresscount);
        }
        // increment addressline variable
        addressline++;
        
        // print hex values
        printf("%02x", c);
        // insert hex value into char array
        output_char[i] = c;
        // increment my i value
        i++; 
        count_char += 2; // because the hex value is 2 char's long increment by 2
        
        
        // essentially used to input spaces between hex #'s
        if(spaceCount==1) {
            printf(" "); // insert space between every 2 hex values
            spaceCount=0;
            // space will be counted as a char
            count_char++;
  
        } else{
          spaceCount++;
        }
        // for hex output split lines every 16 values
        if (byte_count == 15) {
            printf(" "); // to make it more like "xxd" insert another space
            // iterate through hex values and display if it's a valid ASCII char.
            for (int j = 0; j < 16; j++) { 
              if(isprint(output_char[j]))
                  printf("%c", output_char[j]); // valid ascii
               else
                  printf("."); // if not valid, print "."
            }           
            printf("\n"); // insert a new line
            byte_count = 0; // reset byte_count
            addresscount += 1; // add value to address
            addressline = 0; // reset address line
            i = 0; // reset iterating variable to reinsert values in char array
            count_char = 0; // reset counting chars for that line
        } else {
            byte_count += 1; // continue until we get 15
        }
  
      } // while [reading file]
      
      // this part calculates the final line, if it contains less than 16 hex values
      
      // 40 is the number of chars (not including address and its respective
      // space) leading up to ascii output
      int num_space = 40 - count_char; // subtract 40 with num of chars in line
      // insert that many spaces so it aligns with rest of columns
      for (int z = 0; z < num_space; z++) {
          printf(" ");
      }
      // print one more to align with xxd
      printf(" ");
      // output valid ascii characters again 
      for (int j = 0; j < i; j++){
        if(isprint(output_char[j])) {
            printf("%c", output_char[j]);
        } else {
            printf("."); // invalid ascii char
        }
      }
      
      // new line to seperate content
      cout << endl; 
      // close file successfully
      fclose(input);

} // end of do_hex func