#ifndef STACK_H
#define STACK_H

#include "util.h"
#include "rtable.h"


void init_stack(void);

void push(Move move);
void pop(void);

static void _free_stack();


#endif
