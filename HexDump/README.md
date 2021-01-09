# HexDump Program

This program is replica of the Linux command 'xxd' 

## Functionality 

The program will open and read every byte in the file specified by the user when launching the program and write both the ASCII hex value for that byte as well as it’s printable (human-readable) character (characters, digits, symbols) to standard output. For bytes forming non-printable characters, the program will print a ‘.’ character (a dot/period character, i.e. hex value 2E).

The program also provides an option to print in binary instead of hex. This is utilized by using the '-b' flag when executing.

## Example Output: 
```
<address>: <B0B1> <B2B3> <B4B5> <B6B7> <B8B9> <BABB> <BCBD> <BEBF> 123456789ABCDEF
 -- Where B0B1 means Byte #0, Byte #1, etc; the 123456789ABCDEF is the
char/digit/symbol in human readable form
```
 
### Example Hex Output: 
```
0003540: 0504 0675 6e73 6967 6e65 6420 6368 6172 ...unsigned char
0003550: 0008 0107 0000 0131 0675 6e73 6967 6e65 .......1.unsigne
```
### Example Binary Output: 
```
0003540: 00000101 00000100 00000110 01110101 01101110 01110011 ...uns
0003546: 01101001 01100111 01101110 01100101 01100100 00100000 igned
```
## Compiling & Executing

**Compile Instructions:** <br />
To compile this program utilizing the makefile, the user can just enter
"make" in the command line and the program will compile and generate the 'xbd' executable.

If they wanted to manually compile the program and create the 'xbd' executable
"g++ -o xbd xbd_main.cpp".

**Execution Instructions:** <br />
To execute this program the user must enter a few command line arguments. 
The first command line argument must be the executable program 'xbd' then following that
could be either the binary flag (for binary output) or a regular file (for hex output).

If the user wanted to set the binary flag, the user would enter the second argument as -b, and follow it with the input file name. 
For example:
"xbd -b example.txt" would produce a binary output of 'example.txt' HexDump.

The user must pass in either 2 or 3 arguments at any given time and the file passed in must be 
a valid file other wise an error message will be displayed and the program will exit.

If no binary flag is set then automatically the program will assume the user wants the hexadecimal output.
For example:
"xbd example.txt" would produce a hex. output of the 'example.txt'.
