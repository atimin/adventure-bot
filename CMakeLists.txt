cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(bot)
include (${PROJECT_SOURCE_DIR}/avr.cmake)

#====================================================================#
#  Settings                                                          #
#====================================================================#
SET(MAIN_FILE ./main.c ./serial.c)
SET(HDRS ./bot.h ./serial.h)                                # Firmware headers 

ADD_EXECUTABLE(${PROJECT_NAME} ${MAIN_FILE})

AVR_CREATE_HEX()
AVR_UPLOAD(arduino ATmega168 
  /dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A60081kU-if00-port0)
