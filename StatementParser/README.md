# Statement Parser (BNF) Using Flex & Bison
Statement Parser program utilizing Flex & Bison, to recognize and evaluate statements. 

## Functionality 
The Parser will read a file from the directory ("statements.txt"), scan the input, and determine if each statement(s) is valid. The program will then output the statement and whether each statement is 'valid / invalid' into a separate text file ("parsed.txt"). If the statement is invalid the program will output why the statement failed and what it was expecting instead.

Each statement is independent from all other statements, the program will continue evaluating statements until EOF. 

## Statement Specification
id :== identifier, exp :== expression, op :== operator, char :== character

The program will recognize each of the following as valid statements:
- assignment
- expression 

**assignment** shall have the form:
  id = exp;

**expression** shall have the form:
  id op id {op id} -- any length as long as pairs of op and id are added.
  
A parenthesis pair may be used to group any id op id combination. Therefore: id op (id op id) op id AND id op id op (id op id) -- valid expressions 

**Note** - each id, op, =, and ; will have a space as it's precedent and antecedent. The open parenthesis will have a space as it's precedent but it may or may not have a space immediately following it. The converse is true for the closing parenthesis (guaranteed a space as it's antecedent but not necessarily preceding it).

An **id** shall be made up of any combination of **digits** and **char**. The first position of the identifier must contain a char

A **digit** is one of: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 

A **char** is one of: a, b, c, d, e, f, g, h, i, j, k, l m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z

An **op** is one of: ```+, -, *, /, %```

## File Manifest 
### Prior to compiling 
makefile <br />
parser.l (flex) <br />
parser.y (bison) <br />
README.txt <br />
statements.txt <br />

### After compiling & executing 
makefile <br />
parser.l (flex) <br />
parser.y (bison) <br />
README.txt <br />
statements.txt <br />
lex.yy.c <br />
parsed.txt <br />
parser  (executable) <br />
parser.output  (verbose output) <br />
parser.tab.c <br />
parser.tab.h <br />

## Compiling and Executing
### Compile Instructions: 
To compile this program utilizing the makefile, the user can just enter ```make``` in the command line and the program will compile and execute the 'parser' executable. The executable will create the output 'parsed.txt' file.

If they wanted to manually compile the program and create the 'parser' executable: <br />
To compile bison file: <br />
"bison -dv parser.y" <br />
To compile flex file: <br />
"flex parser.l" <br />
To generate 'parser' executable: <br />
"gcc -o parser lex.yy.c parser.tab.c -ly -ll" <br />

### Execution Instructions:
To operate this program all the user has to do is simply type 'make'. The makefile will compile / generate / and execute the proper files. From there, the user may open the 'parsed.txt' file to see the resulting output.

The user must have the proper file already inside the directory, "statements.txt", otherwise the program will not be able to read any input nor output anything.

