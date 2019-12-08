//---------------------------------------------------------------
// File: FUNCTIONS.h
// Purpose: Header file for Function
// Programming Language: C
// Author: Basit Balogun
// Version: 1.0
//---------------------------------------------------------------

#ifndef FUNCTIONS
#define FUNCTIONS
#include "SYMBOLTABLE.h"



extern Var* createE(char *, char *,SymNode*);
extern long int evalFunction(char*,SymNode*);
extern void appendVar(Var*, char*);
extern void printSubsetVF(Var*, char*);
long int evalFunctHelper(Exp*,SymNode*);
long int evaluateFunctFirst(Exp* curr,SymNode*);
long int evaluateFunctHelper2(Exp*,char *,SymNode*);
long int evalSubsetFunct(Var*,SymNode*);
char* evalSubsetFunctHelper(Exp*,char *);
Exp* findSubset(Exp*, char*);
void reverseString(char* str);
extern int isString(char*);


#endif