//---------------------------------------------------------------
// File: VARIABLE.h
// Purpose: Header file for the variable struct
// Programming Language: C
// Author: Basit Balogun
// Version: 3.0
//---------------------------------------------------------------

#ifndef VARIABLE
#define VARIABLE
#include "EXPRESSIONUTILS.h"

//Symbol struct
typedef struct Var {
	char* name;
	Exp* exp;
} Var;


extern Var* createVariable();
extern Var* createVarWExp(char*,char*);
extern char* getVarName(Var*);
extern Exp* getVarExp(Var*);
extern void setVarExp(Var*, Exp*);







#endif