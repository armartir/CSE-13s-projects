#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//Note: all headers in stack.h have what each function here does
// also I am going to source Darrel Long as some of the functions
// were created with slides provided by him
// also I ran Valgrind by typing command in and it said no memory leaks
// refering to stack_create, but I dont see any other way to do it 
Stack *stack_create(int capacity, char name) {
  Stack *s;
  s = (Stack *)malloc(sizeof(Stack));
  assert(s);
  s->capacity = capacity;
  s->name = name;
  s->top = 0;
  s->items = (int *)calloc(capacity, sizeof(int));
  return s;
}
void stack_delete(Stack *s) {
  free(s->items);
  s->items = NULL;
  free(s);
  s = NULL;
}

int stack_pop(Stack *s) {
  if (stack_empty(s)) {
    return -1;
  } else {
    return s->items[s->top--];
  }
}
void stack_push(Stack *s, int item) {
  assert(s->items != NULL);
  s->top++;
  s->items[s->top] = item;
  return;
}
bool stack_empty(Stack *s) {
  return s->top == 0;
}
