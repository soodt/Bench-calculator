#include "infix.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

char outString[100] = "";
//char * poutString;
char ** pfoutString;

int assign_precedence_number(char * args){

  int prec;
  if ((strcmp(args, "+") == 0) || (strcmp(args, "-") == 0 )){
    prec = 1;
  }
  else if ((strcmp(args, "X") == 0) || (strcmp(args, "/") == 0 )){
    prec = 2;
  }
  else  if (strcmp(args, "^") == 0 ){
    prec = 3;
  }
  else  if (strcmp(args, ")") == 0 ){
    prec = 0;
  }
  else prec = -1;
  return prec;
}


// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** args, int nargs) {
  // Write your code here
  int bracketCount = 0;
  struct double_stack * stack = double_stack_new(nargs);
  memset(stack->items, 0, nargs * sizeof(double));
  double_stack_push(stack, 78069);
  //  char outString[100] = "";
   for (int i = 0; i < nargs; i++) {
     if (isdigit(*args[i])==1 || atof(args[i])!=0){ 
       strcat(outString,args[i]);
       strcat(outString," ");
       //   fprintf(stderr, "0,%s, %s\n ", args[i],outString);
       continue;
    }
      else if(strcmp(args[i], "(") == 0 ){
	//  fprintf(stderr, "1,%s, %s\n ", args[i],outString);
	double_stack_push(stack, i);
	bracketCount+=2;
	continue;
    }
      else if(assign_precedence_number(args[i])>0){
	int tempNo;
	int temp;
	//   fprintf(stderr, "2,%s, %s\n ", args[i],outString);
	if ((stack-> top) == 1 ){
	  //  fprintf(stderr, "25,%s, %s\n ", args[i],outString);
	  tempNo = -1;
	}
	else{
	  temp = double_stack_pop(stack);
	  tempNo =  assign_precedence_number(args[temp]);
	  double_stack_push(stack, temp);
	}
	int j = assign_precedence_number(args[i]);
	//  fprintf(stderr, "3,%s, %s\n ", args[i],outString);
	bool activate = false;
	while ((tempNo>0)  && (tempNo>=j)){
	  //   fprintf(stderr, "49,%s, %s,    %d\n ", args[temp],outString,(stack-> top));
	  if ((stack-> top) > 1){
	    temp = double_stack_pop(stack);
	  }
	  strcat(outString,args[temp]);
	  strcat(outString," ");
	  //  fprintf(stderr, "48,%s, %s\n ", args[temp],outString);
	  if ((stack-> top) > 1){
	    temp = double_stack_pop(stack);
	    tempNo = assign_precedence_number(args[temp]);
	    //  fprintf(stderr, "429,%s, %s,    %d\n ", args[temp],outString,(stack-> top));
	    if (strcmp(args[temp], "(") == 0 ){
	      activate = true;
	    }
	   }
	    else{
	      tempNo = -1;
	    }
       	 }
  	 if (activate){
	   //  fprintf(stderr, "4,%s, %s\n ", args[temp],outString);
	  double_stack_push(stack, temp);
	  }
	 //  fprintf(stderr, "5,%s, %s\n ", args[i],outString);
	 double_stack_push(stack, i);
	 continue;
       }
       else if(assign_precedence_number(args[i])==0){
	 //  fprintf(stderr, "6,%s, %s\n ", args[i],outString);
	  int temp2 = double_stack_pop(stack);
	  while(strcmp(args[temp2],"(") != 0){
	    //  fprintf(stderr, "7,%s, %s\n ", args[i],outString);
	    strcat(outString,args[temp2]);
	    strcat(outString," ");
	    temp2 = double_stack_pop(stack);
	  }
	  // fprintf(stderr, "8,%s, %s\n ", args[i],outString);
	  // double_stack_pop(stack);
	  continue;
	}
    }
   //  fprintf(stderr, "9,%s, %s\n ", args[1],outString);
    int temp3 = double_stack_pop(stack);
    while(temp3 != 78069){
      if (strcmp(args[temp3],"(")==0){
	break;
      }
      //  fprintf(stderr, "10,%s, %s\n ", args[temp3],outString);
      strcat(outString,args[temp3]);
      strcat(outString," ");
      temp3 = double_stack_pop(stack);
    }
    int n = 0;
    char *p = strtok (outString, " ");
    char *array[100];
    while (p != NULL)
    {
        array[n++] = p;
        p = strtok (NULL, " ");
    }
    // fprintf(stderr, "11,%s, %s\n ", outString,outString);
    // poutString = outString;
    pfoutString = array;
    nargs = nargs - bracketCount;
    double result = evaluate_postfix_expression(pfoutString,nargs);
    return result;
}


