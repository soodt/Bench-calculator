#include "postfix.h"
#include <math.h>

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {
  struct double_stack * stack = double_stack_new(nargs);
  memset(stack->items, 0, nargs * sizeof(double));
  double element;
  double element2;
  double temp;
  double result;
  for (int i = 0; i < nargs; i++) {
    if (strcmp(args[i], "+") == 0 ){
       element = double_stack_pop(stack);
       //printf("Popped %f from stack\n", element);
       element2 = double_stack_pop(stack);
       // printf("Popped %f from stack\n", element2);
       temp = element + element2;
       double_stack_push(stack, temp);
       //printf("Pushed %f to stack\n", temp);
    }
    else if (strcmp(args[i], "-") == 0 ){
       element = double_stack_pop(stack);
       // printf("Popped %f from stack\n", element);
       element2 = double_stack_pop(stack);
       // printf("Popped %f from stack\n", element2);
       temp = element2 - element;
       double_stack_push(stack, temp);
       //printf("Pushed %f to stack\n", temp);
    }
    else if (strcmp(args[i], "X") == 0 ){
       element = double_stack_pop(stack);
       // printf("Popped %f from stack\n", element);
       element2 = double_stack_pop(stack);
       // printf("Popped %f from stack\n", element2);
       temp = element2 * element;
       double_stack_push(stack, temp);
       // printf("Pushed %f to stack\n", temp);
    }
    else if (strcmp(args[i], "/") == 0 ){
       element = double_stack_pop(stack);
       // printf("Popped %f from stack\n", element);
       element2 = double_stack_pop(stack);
       // printf("Popped %f from stack\n", element2);
       temp = element2 / element;
       double_stack_push(stack, temp);
       //printf("Pushed %f to stack\n", temp);
    }
    else if (strcmp(args[i], "^") == 0 ){
       element = double_stack_pop(stack);
       // printf("Popped %f from stack\n", element);
       element2 = double_stack_pop(stack);
       // printf("Popped %f from stack\n", element2);
       temp = pow(element2,element);
       double_stack_push(stack, temp);
       // printf("Pushed %f to stack\n", temp);
    }
    else{
    element = atof(args[i]);
    double_stack_push(stack, element);
    // printf("Pushed %f to stack\n", element);
    }
  }
  result =  double_stack_pop(stack);
  //printf("Popped %f from stack\n", result);
  return result;
}
