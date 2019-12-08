//---------------------------------------------------------------
// File: VARIABLE.c
// Purpose: C file for the Variable data structure
// Programming Language: C
// Author: Basit Balogun
// Version: 3.0
//---------------------------------------------------------------
#include "FUNCTIONS.h"

//--------------------------------------------
// Function: createE()                                    
// Purpose: creates Expression          
// Preconditions: name and expS and symbol table
// Returns: SymNode*
//--------------------------------------------
Var* createE(char * name, char * expS, SymNode* table){
	//create a variable with the given expression
	Var* foo = createVarWExp("foo", expS);


	//if foo already exist in the table change the value 
	if(findSymNode(table,"foo") != 0){
		SymNode* currNode = findSymNode(table,"foo");
		setVar(currNode, foo);
	}
	else{//if not add it to table
		addToSymTable(table,foo);
		//printf("stopper123\n");
	}
	return foo;
}


//--------------------------------------------
// Function: evalFunction()                                    
// Purpose: evaluates a function and prints        
// Preconditions: name of function and table
// Returns: value
//--------------------------------------------
long int evalFunction(char* eStr,SymNode* table){
	Var* x = createVariable();
	x = findVar(table, eStr);
	return evalFunctHelper(getVarExp(x),table); 
}


//--------------------------------------------
// Function: evalFunctHelper()                                    
// Purpose: evaluates a function and prints        
// Preconditions: name of function and table
// Returns: value
//--------------------------------------------
long int evalFunctHelper(Exp* curr,SymNode* table){
	if(curr->rest == 0){
		return atol(curr->symbol);
	}
	char* symb = (char*)malloc(10 * sizeof(char));//holds operation
	strcpy(symb, curr->symbol);
	long int val = 0;

	//handles cases based on operation
		if (strcmp(symb, "+") == 0){
				val = evaluateFunctFirst(curr->rest,table);//evaluates first item after operator
				if(curr->rest->rest){
						return val + evaluateFunctHelper2(curr->rest->rest, symb,table);
				}
    	}
    	else if(strcmp(symb, "-") == 0){
			if(curr->rest){
				val = evaluateFunctFirst(curr->rest,table);
				if(curr->rest->rest){
						return val - evaluateFunctHelper2(curr->rest->rest, symb,table);
				}
			}
		}
		else if(strcmp(symb,"*") == 0){
			if(curr->rest){
				val = evaluateFunctFirst(curr->rest,table);

				if(curr->rest->rest){
						return val * evaluateFunctHelper2(curr->rest->rest, symb,table);
				}
			}
		}
		return val;//if it gets here there is only one exp after the operator
}




//--------------------------------------------
// Function: evaluateFuctFirst(Exp* curr)                                    
// Purpose: Evaluates an of one Exp*      
// Preconditions: None
// Returns: long int
//--------------------------------------------
long int evaluateFunctFirst(Exp* curr, SymNode* table){
	if(curr->first) return evalFunctHelper(curr->first, table);
	else{
			//if function or variable
			if(isString(curr->symbol)){
				return evalFunction( curr->symbol,table);
			}
			//if number
			return atol(curr->symbol);
		}
}


//--------------------------------------------
// Function: evaluateFunctHelper2(Exp* curr,char *symb)                                   
// Purpose: helper method for evaluate          
// Preconditions: None
// Returns: long int value of the evaluated exp
//--------------------------------------------
long int evaluateFunctHelper2(Exp* curr,char *symb,SymNode* table){

	//if Expression has an inner expression of type "(<operator> <space separated list of operands>)" 
	if(curr->first){
		if(!curr->rest){
			return evalFunctHelper(curr->first, table);
		}
		else{//if first has a rest

			if (strcmp(symb, "+") == 0){
					return evalFunctHelper(curr->first,table) + evaluateFunctHelper2(curr->rest,symb, table);
	    	}

	    	else if(strcmp(symb,"-") == 0){
				return evalFunctHelper(curr->first,table) + evaluateFunctHelper2(curr->rest,symb, table);
			}
			
			else if(strcmp(symb,"*") == 0){
				return evalFunctHelper(curr->first, table) * evaluateFunctHelper2(curr->rest,symb, table);
			}
		}
	} 

	else{
		//handles cases based on operation
		if (strcmp(symb, "+") == 0){
			if(!curr->rest) return evaluateFunctFirst(curr, table);

			else{
				return evaluateFunctFirst(curr,table) + evaluateFunctHelper2(curr->rest,symb,table);
			}
			
    	}

    	else if(strcmp(symb,"-") == 0){
			if(!curr->rest) return evaluateFunctFirst(curr,table);

			else{
				return evaluateFunctFirst(curr,table) + evaluateFunctHelper2(curr->rest,symb,table);
			}
		}
		
		else if(strcmp(symb,"*") == 0){
			if(!curr->rest) return evaluateFunctFirst(curr, table);

			else{
				return evaluateFunctFirst(curr,table) * evaluateFunctHelper2(curr->rest,symb, table);
			}
		}
	}
}

//--------------------------------------------
// Function: appendVar()                                    
// Purpose: appends Exp in the variable       
// Preconditions: name of function/var and appendStr
// Returns: value
//--------------------------------------------
void appendVar(Var* v, char* appendStr){
	Exp* e = createExpNode();
	e = getVarExp(v);
	appendExpression(e,appendStr);
	setVarExp(v, e);
}



//--------------------------------------------
// Function: printSubsetVF()                                    
// Purpose: prints subset of the given var      
// Preconditions: name of function/Var and appendStr
// Returns: value
//--------------------------------------------
void printSubsetVF(Var* v, char* s){
	Exp* e = createExpNode();
	e = getVarExp(v);
	printSubset(e,s);
}



//--------------------------------------------
// Function: isString()                                    
// Purpose: check if char* is a string     
// Preconditions: x
// Returns: 1 or 0
//--------------------------------------------
int isString(char* x){
	for (int i = 0; i < strlen(x);i++){
		if(isalpha(x[i])) return 1;
	}
	return 0;
}