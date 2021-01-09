# SIC/XE Disassembler Program

Disassembler Program for the XE variant of the SIC/XE family of machines

## Functionality 

The XE disassembler program shall open an XE object file, <filename>.obj and its
accompanying symbol file, <filename>.sym, then it will disassemble the object code,
and generate an XE source file, <filename.sic> and an XE listing file,
<filename>.lis using the disassembled code. The symbol file, <filename>.sym will
contain the SYMTAB and LITTAB the assembler generated when assembling the object
file.
  
Once the program has been compiled an executable named ‘dis’ will be generated. To run the program, the user shall
provide the filename on the command line when starting/running the disassembler:
```% dis <filename>``` <br />
the disassembler will then use “filename” for the name of the source file it
generates, <filename>.sic, and the accompanying listing file, <filename>.lis.
Note, the symbol file <filename>.sym will be provided with the object code file.
If neither the <filename>.obj or <filename>.sym are present, the dis program shall
gracefully exit.
  
 **NOTE:** The .obj file and .sym file must have the same name for this program to execute as needed.
 
 ## Compiling & Executing
 Compile Instructions: To compile this program utilizing the makefile, the user can just enter
```make``` in the command line and the program will compile and generate the 'dis' executable.

If they wanted to manually compile the program and create the 'dis' executable
```g++ -o dis disassembler.cpp```.

Operating Instructions:
To operate this program the user must enter a few command line arguments. 
The first command line argument must be the executable program 'dis' then following that
will be only the name of the symbol and object files with NO extension.

Meaning in order to run the program correctly, the symbol and object files MUST HAVE the same name (only with different extensions).
For example:
"dis sample" would produce the disassembled sample.sic and sample.lis files from the files "sample.sym" and "sample.obj"

The user must pass in either 2 arguments at any given time and the input passed in must be valid files AND must have coinciding names with both the .obj and .sym files, other wise an error message will be displayed and the program will exit.

I originally implemented the input to take in the file names with extension, in any order. But deemed the new process was cleaner and more efficient. 
