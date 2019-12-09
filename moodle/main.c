//---------------------------------------------------------------
// File: main.c
// Purpose: Allow different functions to be made on Expressions 
//			based on terminal input
// Programming Language: C
// Author: Basit Balogun
// Version: 3.0
// 
// Commands:
// • ’c’: create a new expression. The next line contains the expression. A new data structure
// 		is created and the current expression will point to it. The current expression is stored as the
// 		variable foo.
// • ’p’: print the variable named on the next line
// • ’e’: evaluate the expression named on the next line (arithmetically)
// • ’a’: append a new expression to the current expression. The new expression is given on the
//		next line
// 		Assuming the current expression is: ”(+ 1 2 3)”.
// 		Appending ”4” would result in ”(+ 1 2 3 4)”, while appending ”(+ 4)” would result in ”(+ 1
// 		2 3 (+ 4))”
// • ’s’: prints a subset of the expression. The subset specification is on the next line and uses ’f’
// 		(first) and ’r’ (rest)
// 		For example, if the current expression is ”(+ 2 (- 3 4) 5)”
// 		– ”f” results in ”+”
// 		– ”r f” results in ”2”
// 		– ”f f” does not make sense
// 		– ”r r f” results in ”(- 3 4)”
// • ’v’: define a variable. The next line contains the variable and the line after that contains the
// 		expression. A new data structure is created to contain the expression.
// • ’d’: define a function (without parameters). The next line contains the function name and
// 		the line after that contains the expression. A new data structure is created to contain the
// 		expression.
// • ’l’: define a function with parameters. The next line contains the function name, the line
// 		after that the parameters, and then a line that contains the expression. A new data structure
// 		is created to contain the expression.
//---------------------------------------------------------------
#include "FUNCTIONS.h"

int main(){


	Exp* curr = createExpNode();
	SymNode* table = createSymNode();
	Var* currV = createVariable();
	printf("%s\n","Insert command or type \"Exit\" to exit " );
	char c = '0';//holds command
	char* cStr = (char*)malloc(100*sizeof(char));
	char* pStr = (char*)malloc(100*sizeof(char));
	char* aStr = (char*)malloc(100*sizeof(char));

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
		}

		//Handles subset
		else if(c == 's'){
			cStr = (char*)malloc(100*sizeof(char));
			fgets(cStr,100,stdin);
			fgets(cStr,100,stdin);
			printSubsetVF(currV,cStr);
		}

		//Handles evaluate
		else if(c == 'e'){
			cStr = (char*)malloc(100*sizeof(char));
			fgets(cStr,100,stdin);
			fgets(cStr,100,stdin);

			if(cStr[strlen(cStr) -1] == 10){
				cStr[strlen(cStr) -1] = 0;
			}

			printf("%ld\n", evalFunction(cStr,table));
		}


		//Handles defining variables and functions without parameters
		else if(c == 'v' || c == 'd'){
			cStr = (char*)malloc(100*sizeof(char));
			pStr = (char*)malloc(100*sizeof(char));
			fgets(cStr,100,stdin);
			fgets(cStr,100,stdin);

			fgets(pStr,100,stdin);
			//fgets(eStr,100,stdin);

			if(cStr[strlen(cStr) -1] == 10){
				cStr[strlen(cStr) -1] = 0;
			}

			if(pStr[strlen(pStr) -1] == 10){
				pStr[strlen(pStr) -1] = 0;
			}
			
			createE(cStr,pStr,table);
			
		}


		//Handles defining variables and functions without parameters
		else if(c == 'l'){
			printf("Fucntionality for functions without parameter not implemented\n");
		}
	}
	return 0;	
}

