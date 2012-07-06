#ifndef SERVO_H
#define SERVO_H

#include <avr/io.h>
#include <inttypes.h>

#define MIN_SERVO_PWM     10
#define MAX_SERVO_PWM     30
#define MIN_SERVO_DEGS    30
#define MAX_SERVO_DEGS    150

extern void init_pwm();
extern void servo(volatile uint8_t *serv, uint8_t degs);

#endif
