# Statement Parser (BNF) Using Flex & Bison
Statement Parser program which recognizes and evaluates valid statements 

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
