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
	Exp* ex = createExpNode();
	ex = getVarExp(x);

	//if expression function of subsets 
	char* temp = (char*)malloc(100*sizeof(char));
	temp = ex->symbol;

	//if "f" or"r"
	if(strcmp(temp,"f") == 0 || strcmp(temp,"r") == 0){
		return evalSubsetFunct(x,table);
	}

	return evalFunctHelper(ex,table); 
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
// Function: evalSubsetFunct()                                    
// Purpose: evaluates functions with subsets        
// Preconditions: Var* of functions with 
//				  subsets and table
// Returns: value
//--------------------------------------------
long int evalSubsetFunct(Var* ex,SymNode* table){
	Exp* exp = createExpNode();
	exp = getVarExp(ex);

	char* temp = (char*)malloc(100*sizeof(char));
	char* varName = (char*)malloc(100*sizeof(char));
	varName = evalSubsetFunctHelper(exp,temp);

	//reverse temp
	reverseString(temp);


	//find variable and get its expression
	Var* x = createVariable();
	x = findVar(table, varName);
	exp = getVarExp(x);


	//find subsetExp and evaluates 
	exp = findSubset(exp,temp);
	return evalFunctHelper(exp,table);
}




//--------------------------------------------
// Function: findSubset()                                    
// Purpose: find subset Exp*       
// Preconditions: Exp holding subset and
//		char* of r and f
// Returns: value
//--------------------------------------------
Exp* findSubset(Exp* exp, char* s){
	Exp* pntr = exp;

	//goes through the list of characters
	for(int i = 0; i < strlen(s);i = i+2){
		//if 'f' go to first
		if(s[i]  == 'f'){
			if(pntr->first == 0){
				if(pntr->symbol != 0){
					return pntr;
				}
			}
			pntr = pntr->first;
		}

		//if 'r' go to rest
		if(s[i]  == 'r'){
			if(pntr->rest == 0){
				return 0;
			}
			pntr = pntr->rest;
		}
	}
	return pntr;
}

//--------------------------------------------
// Function: evalSubsetFunctHelper()                                    
// Purpose: helper for evalSubsetFunct       
// Preconditions: Exp* of functions with 
//				  subsets
// Returns: variable name of Subset
//--------------------------------------------
char* evalSubsetFunctHelper(Exp* ex, char* c){
	Exp* temp = createExpNode();
	temp = ex;

	//loop through until you find functioname
	while(temp){

		//takes subset
		if(temp->symbol){
		  strcat(c,temp->symbol);
		}


		//if it is the variable name
		if(temp->rest->symbol){
			return temp->rest->symbol;
		}

		//if there is an additional subset symbol
		if(temp->rest->first){
			strcat(c," ");
			temp = temp->rest->first;
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


//--------------------------------------------
// Function: reverseString()                                    
// Purpose: reverses a string    
// Preconditions: x
// Returns: void
// Source: geeksforgeeks
//--------------------------------------------
void reverseString(char* str) 
{ 
    int l, i; 
    char *begin_ptr, *end_ptr, ch; 
  
    // Get the length of the string 
    l = strlen(str); 
  
    // Set the begin_ptr and end_ptr 
    // initially to start of string 
    begin_ptr = str; 
    end_ptr = str; 
  
    // Move the end_ptr to the last character 
    for (i = 0; i < l - 1; i++) 
        end_ptr++; 
  
    // Swap the char from start and end 
    // index using begin_ptr and end_ptr 
    for (i = 0; i < l / 2; i++) { 
  
        // swap character 
        ch = *end_ptr; 
        *end_ptr = *begin_ptr; 
        *begin_ptr = ch; 
  
        // update pointers positions 
        begin_ptr++; 
        end_ptr--; 
    } 
} 