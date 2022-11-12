#ifndef _PWM_H_
#define _PWM_H_

#define FREQUENCY 1 // kHz, so t_on is in ms
#define DUTY_CYCLE_STEP 1 // [0:DUTY_MAX/STEP]
#define DUTY_MIN 0 // time in microseconds
#define DUTY_MAX 1000 // time in microseconds, max value differs depending on PERIOD

#endif