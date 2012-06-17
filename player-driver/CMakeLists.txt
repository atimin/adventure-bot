#----------------------------------
# Driver for the Player server
#----------------------------------

SET (CMAKE_MODULE_PATH "@CMAKE_INSTALL_PREFIX@/share/cmake/Modules")
INCLUDE (UsePlayerPlugin)

FIND_LIBRARY(MODBUS_LIB modbus
  DOC "The ModBus library" )
MESSAGE(${MODBUS_LIB})
LINK_LIBRARIES(${MODBUS_LIB})

PLAYER_ADD_PLUGIN_DRIVER (adventurebot SOURCES adventurebot.cpp)
FILE(COPY ./bot.cfg DESTINATION ./ )
