#ifndef _task_h_
#define _task_h_

#include "headfile.h"

extern int straight;
extern int if_stop;
extern int transformation;
extern int if_black;
extern uint8_t mode;

typedef void (*StateHandler)(void);
extern StateHandler task_mode[];

void task_1(void);
void task_2(void);
void task_3(void);
void task_4(void);


#endif
