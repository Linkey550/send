#ifndef __motor_H
#define	__motor_H

#include "stm32f1xx.h"
#include "main.h"

 void set_go(void);
 void set_turn_left(void);
 void set_turn_right(void);
 void set_stop(void);
 void pid_go(void);
 void set_stright_go(int longnumber_set);
 void set_stright_turnleft(int longnumber_set);
 void set_stright_turnright(int longnumber_set);
 void openmv_turnright(void);
 void openmv_turnleft(void);
#endif

