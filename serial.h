#ifndef SERIAL_H
#define SERIAL_H

#include <inttypes.h>

#define MAX_RX_BUFF_SIZE 50

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

extern serial_t* serial_create();
extern void serial_destroy(serial_t *sp);
extern int8_t serial_config(serial_t *sp, baud_t baudrate, 
    volatile uint8_t *rx_port, uint8_t rx_pin, volatile uint8_t *tx_port, uint8_t tx_pin);
extern int8_t serial_debug(serial_t *sp, volatile uint8_t *debug_port, uint8_t debug_pin);
extern int8_t serial_handle(serial_t *sp);
extern int8_t serial_write_bytes(serial_t *sp, uint8_t* buff, uint8_t size);
#endif
