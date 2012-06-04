/*
 * Software serial port module for AVR microcontrollers
 * 2012 Aleksey Timin
 *
 * Public Domain
 * */
#ifndef SERIAL_H
#define SERIAL_H

#include <inttypes.h>

#define MAX_RX_BUFF_SIZE 50

/* Supported speeds. */
typedef enum {
  BAUD_300,
  BAUD_1200,
  BAUD_2400,
  BAUD_4800,
  BAUD_9600,
  BAUD_19200,
  BAUD_28800,
  BAUD_31250,
  BAUD_38400,
  BAUD_57600,
  BAUD_115200
} baud_t;

/* Serial port */
typedef struct 
{
  uint16_t baudrate;

  uint8_t  rx_index;
  uint8_t  rx_buff[MAX_RX_BUFF_SIZE];

  uint8_t  delay_rxcenter;
  uint8_t  delay_rxintra;
  uint8_t  delay_rxstop;
  uint8_t  delay_tx;

  volatile uint8_t  *rx_port;
  uint8_t  rx_pin;
  volatile uint8_t  *tx_port;
  uint8_t  tx_pin;

  uint8_t  debug;
  volatile uint8_t  *debug_port;
  uint8_t  debug_pin;
} serial_t;

/* Allocate memory for serial port. */
extern serial_t* serial_create();

/* Free serial port object.
 * @param *sp a serial port. */
extern void serial_destroy(serial_t *sp);

/* Configurate port.
 * @param *sp a serial port.
 * @param baudrate a rate of serial port.
 * @param *rx_port an address of RX port.
 * @param rx_pin a number of RX pin.
 * @param *tx_port an address of TX port.
 * @param tx_pin a number of TX pin.
 * @return 1 - success, 0 - fault. */
extern int8_t serial_config(serial_t *sp, baud_t baudrate, 
    volatile uint8_t *rx_port, uint8_t rx_pin, volatile uint8_t *tx_port, uint8_t tx_pin);

/* Turn on debug mode.
 *
 * @param *sp a serial port.
 * @param *tx_port an address of DEBUG port.
 * @param tx_pin a number of DEBUG pin. 
 * @return 1 - success, 0 - fault. */
extern int8_t serial_debug(serial_t *sp, volatile uint8_t *debug_port, uint8_t debug_pin);

/* Handle to receive byte by port. Usually it uses in interrupts.
 * @param *sp a serial port.
 * @return 1 - success, 0 - fault. */
extern int8_t serial_handle(serial_t *sp);

/* Write array of bytes to serial port
 * @param *sp a serial port.
 * @param *buff a array of byte.
 * @param size a size of array.
 * @return 1 - success, 0 - fault. */
extern int8_t serial_write_bytes(serial_t *sp, uint8_t *buff, uint8_t size);

/* Write string to serial port 
 * @param *sp a serial port.
 * @param msg a string for sending.
 * @return 1 - success, 0 - fault. */
extern int8_t serial_print(serial_t *sp, const char *msg);

/* Read bytes from serial port 
 * @param *sp a serial port.
 * @param *buff a array of byte.
 * @param size a size of array.
 * @return size of read bytes (-1 error) */
extern int8_t serial_read_bytes(serial_t *sp, uint8_t *buff, uint8_t size);
#endif
