//---------------------------------------------------------------
// File: SYMBOLTABLE.c
// Purpose: C file for the Symbol table
// Programming Language: C
// Author: Basit Balogun
// Version: 3.0
//---------------------------------------------------------------
#include "SYMBOLTABLE.h"


//--------------------------------------------
// Function: createSymNode()                                    
// Purpose: creates head of symbol table           
// Preconditions: none
// Returns: SymNode*
//--------------------------------------------
SymNode* createSymNode(){
	SymNode* x = (SymNode*)calloc(1,sizeof(SymNode));
	return x;
}

//--------------------------------------------
// Function: setVar()                                    
// Purpose: sets variable          
// Preconditions: StmNode* Var
// Returns: SymNode*
//--------------------------------------------
void setVar(SymNode* s,Var* v){
	s->var = v;
}



//--------------------------------------------
// Function: addToSymTable()                                    
// Purpose: adds to the end of the symbol table           
// Preconditions: SymNode* and Var*
// Returns: void
//--------------------------------------------
void addToSymTable(SymNode* sN, Var* v){
	SymNode* pntr = sN;
	size++;

	//If first element
	if(pntr->var == 0){
		setVar(pntr, v);
		return;
	}

	//look for last element
	while(pntr->next != 0){
		pntr = pntr->next;
	}

	SymNode* newNode = createSymNode();
	setVar(newNode, v);
	pntr->next = newNode;

}



//--------------------------------------------
// Function: findVar()                                    
// Purpose: returns Variable with given name        
// Preconditions: Table head node, char* name
//				  to find
// Returns: Var*
//--------------------------------------------
Var* findVar(SymNode* head, char* s){
	SymNode* pntr = head;


	while(pntr){
		Var* curr = pntr->var;

		if(strcmp(getVarName(curr),s)  == 0){
			return curr;
		}
		pntr = pntr->next;
	}
	return 0;
}


//--------------------------------------------
// Function: findSymNode()                                    
// Purpose: finds the Node with name        
// Preconditions: SymNode* char*
// Returns: SymNode*
//--------------------------------------------
SymNode* findSymNode(SymNode* head,char* s){
	SymNode* pntr = head;

	while(pntr){
		Var* curr = pntr->var;
		if(curr == 0) return 0;

		if(strcmp(getVarName(curr),s)  == 0){
			return pntr;
		}
		pntr = pntr->next;
	}
	return 0;
}

//--------------------------------------------
// Function: tableSize()                                    
// Purpose: returns the number of items in the
//			table         
// Preconditions: none
// Returns: int size
//--------------------------------------------
int tableSize(){
	return size;
}