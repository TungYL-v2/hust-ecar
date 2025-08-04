#ifndef _task_h_
#define _task_h_

#include "headfile.h"

volatile extern uint8_t straight;
volatile extern uint8_t if_stop;
volatile extern uint8_t transformation;
volatile extern uint8_t if_black;
volatile extern uint8_t mode;
volatile extern uint8_t task2_flag;
volatile extern uint8_t quan_max;
volatile extern uint8_t situation;
typedef void (*StateHandler)(void);
extern StateHandler task_mode[];

void detmdc_init(void);
uint8_t det_medicine(void);

void task_1(void);
void task_2(void);
void task_3(void);

volatile extern uint8_t flag;
volatile extern uint8_t quan;
void sing(void);
void car_stop(void);
void low_speed(int time);
void high_speed(int time);
void text_3_4(void);


#endif
