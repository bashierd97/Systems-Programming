//======= CS 530 Project 3 ~ Statement Parser: Bison File ======= 
//Project Creators: Bashier Dahman 
//Class Information: CS 530, Fall 2020
//Assignment Information: Project #3, Statement Parser 
//Filename: parser.y

%{
/* C declarations used in actions */
#include <stdio.h>
// functions and variables to be used by both bison & flex
extern int yylex();
extern char* yytext;
extern void yyerror();
extern char* buffer;
extern void outputFile();
// file variables to read input and output to file
extern FILE* yyin;
extern FILE* yyout;
%}
// used to define our own error handling
%define parse.error verbose
// defining our tokens
%token IDENTIFIER DIGIT
%token PAREN_OPEN PAREN_CLOSE
%token EQUAL SEMI_COLON OPERATOR
%token NEWLINE OTHER END_OF_FILE
%%

/* descriptions of expected inputs  corresponding actions (in C) */

PROGRAM : assignment NEWLINE        {outputFile();}
      
      | EXPR NEWLINE                {outputFile();}
      
      | PROGRAM assignment NEWLINE  {outputFile();}
      
      | PROGRAM EXPR NEWLINE        {outputFile();}
      
      | PROGRAM error NEWLINE       {fprintf(yyout,buffer);}
      
      | error NEWLINE               {fprintf(yyout,buffer);}
      
      | PROGRAM NEWLINE             {}
      
      | NEWLINE                     {}
;

/* assignment */
assignment : IDENTIFIER EQUAL EXPR SEMI_COLON		
;
/* expression */
EXPR : IDENTIFIER OPERATOR IDENTIFIER | PAREN_OPEN EXPR PAREN_CLOSE | EXPR OPERATOR IDENTIFIER | IDENTIFIER OPERATOR PAREN_OPEN EXPR PAREN_CLOSE
;

%%                     

/* C code */
int main (void) {
  // open and read 'statements.txt'
	yyin = fopen("statements.txt","r");
  // write output to 'parsed.txt'
  yyout = fopen("parsed.txt", "w");
	// function for parse
  yyparse();
  // return successfully
	return 0;
} // main




