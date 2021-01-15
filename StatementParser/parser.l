/*======= CS 530 Project 3 ~ Statement Parser: Flex File ======= 
//Project Creators: Bashier Dahman
//Class Information: CS 530, Fall 2020
//Assignment Information: Project #3, Statement Parser 
//Filename: parser.l */

%{
/* include proper header files */
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
/* external variables and functions*/
void extern yyerror(char*);
void extern outputFile();
char *buffer;
int get_size;
%}

/* tell flex to read only one input file*/
%option noyywrap
/* setting reg ex to match nums & chars*/
numbers                 ([0-9])+  
character               ([a-zA-Z])+
alphanumeric            ([a-zA-Z0-9])+

%%

{numbers}                     {fprintf(yyout,"%s", yytext);  return (DIGIT);}
{character}{alphanumeric}*	  {fprintf(yyout,"%s", yytext);  return (IDENTIFIER);}
[\n]                          {return NEWLINE;}
[ \t\r\v\f]		                {fprintf(yyout,"%s", yytext);}
[-+*/%]                       {fprintf(yyout,"%s", yytext); return OPERATOR;}
[;]                           {fprintf(yyout,"%s", yytext); return SEMI_COLON;}
[=]                           {fprintf(yyout,"%s", yytext); return EQUAL;}
[(]                           {fprintf(yyout,"%s", yytext); return PAREN_OPEN;}
[)]                           {fprintf(yyout,"%s", yytext); return PAREN_CLOSE;}
. 			                      {fprintf(yyout,"%s", yytext);}

%%

// function used to output valid statement to file
void outputFile() {
    fprintf(yyout,"\n-- valid\n");
}

// yyerror() handles any syntax based errors and outputs the error
// to the file as well
void yyerror(char *reason) {
    get_size = snprintf(NULL, 0, "\n-- invalid: Invalid %s\n", reason);
    buffer = (char *)malloc(get_size + 1);
    // print to buffer, to print out to file
    snprintf(buffer, get_size+1, "\n-- invalid: Invalid %s\n\n", reason);
}

