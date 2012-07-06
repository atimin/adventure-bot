#include "servo.h"

void init_pwm()
{
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
  TCCR0B = _BV(CS02) | _BV(CS00);
}

void servo(volatile uint8_t* serv, uint8_t degs)
{
  if (degs > MAX_SERVO_DEGS)
    degs = MAX_SERVO_DEGS;
  if (degs < MIN_SERVO_DEGS)
    degs = MIN_SERVO_DEGS;

  *serv = MIN_SERVO_PWM + (MAX_SERVO_PWM - MIN_SERVO_PWM)*(degs - MIN_SERVO_DEGS) 
    / (MAX_SERVO_DEGS - MIN_SERVO_DEGS);
}


