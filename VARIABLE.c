//---------------------------------------------------------------
// File: VARIABLE.c
// Purpose: C file for the Variable data structure
// Programming Language: C
// Author: Basit Balogun
// Version: 3.0
//---------------------------------------------------------------
#include "VARIABLE.h"


//--------------------------------------------
// Function: createVariable()                                    
// Purpose: creates a Variable            
// Preconditions: varName
// Returns: Exp*
//--------------------------------------------
Var* createVariable(){
	Var* x = (Var*)calloc(1,sizeof(Var));
	return x;
}






//--------------------------------------------
// Function: createVariableWExp()                                    
// Purpose: creates a Variable            
// Preconditions: varName and Exp string
// Returns: Exp*
//--------------------------------------------
Var* createVarWExp(char* name,char* expS){
	Var* x = (Var*)calloc(1,sizeof(Var));
	x->name = name;
	x->exp = createExp(expS);
	return x;
}



//--------------------------------------------
// Function: getVarName()                                    
// Purpose: returns the name of the var            
// Preconditions: Var*
// Returns: Exp*
//--------------------------------------------
char* getVarName(Var* v){
	return v->name;
}

//--------------------------------------------
// Function: getExp()                                    
// Purpose: returns the Exp* of the var            
// Preconditions: Var*
// Returns: Exp*
//--------------------------------------------
Exp* getVarExp(Var* v){
	if(!v->exp) {
		printf("Var has no expression\n");
		return 0;
	}
	return v->exp;
}


//--------------------------------------------
// Function: setVarExp()                                    
// Purpose: set exp            
// Preconditions: Var* Exp*
// Returns: void
//--------------------------------------------
void setVarExp(Var* v, Exp* e){
	v->exp = e;
}

