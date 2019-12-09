//---------------------------------------------------------------
// File: SYMBOLTABLE.h
// Purpose: Header file for the symbol table
// Programming Language: C
// Author: Basit Balogun
// Version: 3.0
//---------------------------------------------------------------

#ifndef SYMBOLTABLE
#define SYMBOLTABLE
#include "VARIABLE.h"

//Symbol table implemented as  a linkedlist
typedef struct SymNode{
	Var* var;
	struct SymNode* next;//holds next item
} SymNode;


extern SymNode* createSymNode();
extern void setVar(SymNode*, Var*);
extern void addToSymTable(SymNode*,Var*);
extern Var* findVar(SymNode*, char*);
extern SymNode* findSymNode(SymNode*,char*);
extern int tableSize();
int size;






#endif