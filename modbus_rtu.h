/*
 * RTU slave implimentation for AVR microcontrollers
 * 2012 Aleksey Timin
 *
 * Public Domain
 * */
#ifndef MODBUS_RTU_H

#include <inttypes.h>
#include "serial.h"

#define MODBUS_RTU_H

typedef struct _mb_rtu_t {
  uint8_t uid;
  serial_t *sp;

} mb_rtu_t;

/* Allocate memory for modbus object.
 * @return modbus_rtu. */
extern mb_rtu_t* mb_rtu_create();

/* Free modbus object. 
 * @param *mb a pointer to modbus struct. */
extern void mb_rtu_destroy(mb_rtu_t *mb);

/* Initialization modbus.
 * @param *mb a pointer to modbus struct
 * @param uid a modbus slave address
 * @param *sp a serial port */
extern void mb_rtu_config(mb_rtu_t *mb, uint8_t uid, serial_t *sp);

/* Read buffer of serial port and process request 
 * @param *mb a pointer to modbus struct
 * @param *map  a map modbus registers
 * @param szie a map size
 * @return 1 - a map has been changed. */
extern uint8_t mb_rtu_proc(mb_rtu_t *mb, uint16_t *map, uint8_t size);

#endif /* end of include guard: MODBUS_RTU_H */
