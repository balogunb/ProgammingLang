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
extern long int evalFunctHelper(Exp*,SymNode*);
extern long int evaluateFunctFirst(Exp* curr,SymNode*);
extern long int evaluateFunctHelper2(Exp*,char *,SymNode*);
extern long int evalSubsetFuct(char*,SymNode*);


extern int isString(char*);


#endif