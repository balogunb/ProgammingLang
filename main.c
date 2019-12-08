//---------------------------------------------------------------
// File: main.c
// Purpose: Allow different functions to be made on Expressions 
//			based on terminal input
// Programming Language: C
// Author: Basit Balogun
// Version: 3.0
// 
// Commands:
// ’c’: create a new expression. The next line contains the expression. A new data structure is
// created and the current expression will point to it.
// • ’p’: print the current expression
// • ’e’: evaluate the current expression (arithmetically)
// • ’a’: append a new expression to the current expression. The new expression is given on the
// 		  next line
// 		  Assuming the current expression is: ”(+ 1 2 3)”.
// 		  Appending ”4” would result in ”(+ 1 2 3 4)”, while appending ”(+ 4)” would result in ”(+ 1
// 		  2 3 (+ 4))”
// • ’s’: prints a subset of the expression. The subset specification is on the next line and uses ’f’
//		  (first) and ’r’ (rest)
// • "Print": terminates the program
//---------------------------------------------------------------
#include "FUNCTIONS.h"




Exp* test(){

	//Test append single number -> 
	Exp* head = createExp("(+ 2 4 7)");
	printExpression(head);

	// appendExpression(head,"4");
	// appendExpression(head, "(- 4 4)");
	// appendExpression(head, "5");
	// appendExpression(head, "(- 4 5 (+ 2 3) (-5 6))");

	return head;
}

int main(){
	Exp* curr = createExpNode();
	SymNode* table = createSymNode();
	Var* currV = createVariable();
	printf("%s\n","Insert command or type \"Exit\" to exit " );
	char c = '0';//holds command
	char* cStr = (char*)malloc(100*sizeof(char));//String for create
	char* pStr = (char*)malloc(100*sizeof(char));//String for print
	char* aStr = (char*)malloc(100*sizeof(char));//String for append
	char* sStr = (char*)malloc(100*sizeof(char));//String for subset
	char* vStr = (char*)malloc(100*sizeof(char));//String for variableName
	char* eStr = (char*)malloc(100*sizeof(char));//String for expression and eval

	//Exit terminates the program
	while( c != 'q'){
		c = getchar();

		//Handles create
		if(c == 'c'){
			free(curr);
			cStr = (char*)malloc(100*sizeof(char));
			fgets(cStr,100,stdin);
			fgets(cStr,100,stdin);

			if(cStr[strlen(cStr) -1] == 10){
				cStr[strlen(cStr) -1] = 0;
			}
			currV = createE("foo",cStr,table);
			//printf("stopper\n");
		}

		//Handles print
		else if(c == 'p'){
			pStr = (char*)malloc(100*sizeof(char));
			fgets(pStr,100,stdin);
			fgets(pStr,100,stdin);

			if(pStr[strlen(pStr) -1] == 10){
				pStr[strlen(pStr) -1] = 0;
			}


			//create a new variable for find var here
			//so curr would always be foo if need be
			currV = findVar(table,pStr);
			printExpression(getVarExp(currV));
		}

		//Handles Append
		else if(c == 'a'){
			aStr = (char*)malloc(100*sizeof(char));
			fgets(aStr,100,stdin);
			fgets(aStr,100,stdin);

			if(aStr[strlen(aStr) -1] == 10){
				aStr[strlen(aStr) -1] = 0;
			}

			appendVar(currV, aStr);

			//appendExpression(curr,aStr);

			//free(appendStr);
			//char x;
		}

		//Handles subset
		else if(c == 's'){
			sStr = (char*)malloc(100*sizeof(char));
			fgets(sStr,100,stdin);
			fgets(sStr,100,stdin);
			printSubsetVF(currV,sStr);
			//free(subset);
		}
		else if(c == 'e'){
			eStr = (char*)malloc(100*sizeof(char));
			fgets(eStr,100,stdin);
			fgets(eStr,100,stdin);

			if(eStr[strlen(eStr) -1] == 10){
				eStr[strlen(eStr) -1] = 0;
			}

			printf("%ld\n", evalFunction(eStr,table));
		}


		//Handles defining variables and functions without parameters
		else if(c == 'v' || c == 'd'){
			vStr = (char*)malloc(100*sizeof(char));
			eStr = (char*)malloc(100*sizeof(char));
			fgets(vStr,100,stdin);
			fgets(vStr,100,stdin);

			fgets(eStr,100,stdin);
			//fgets(eStr,100,stdin);

			if(vStr[strlen(vStr) -1] == 10){
				vStr[strlen(vStr) -1] = 0;
			}

			if(eStr[strlen(eStr) -1] == 10){
				eStr[strlen(eStr) -1] = 0;
			}
			

			//set make newV curr v to allow most recent v to be curr
			Var* newV = createVarWExp(vStr,eStr);
			addToSymTable(table,newV);
			
		}
	}
	return 0;	
}

