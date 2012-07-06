#====================================================================#
#  Settings                                                          #
#====================================================================#

INCLUDE (./avr.cmake)

SET(MAIN_FILE ./main.c ./serial.c ./modbus_rtu.c ./adc.c)
SET(HDRS ./bot.h ./serial.h ./modbus_rtu.h ./adc.h)                                # Firmware headers 


ADD_EXECUTABLE(${PROJECT_NAME} ${MAIN_FILE})

AVR_CREATE_HEX()
AVR_UPLOAD(arduino ATmega168 
  /dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A60081kU-if00-port0)
