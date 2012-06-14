CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
PROJECT(bot)
INCLUDE (${PROJECT_SOURCE_DIR}/avr.cmake)

SET (CMAKE_MODULE_PATH "@CMAKE_INSTALL_PREFIX@/share/cmake/Modules")
INCLUDE (UsePlayerPlugin)

ADD_SUBDIRECTORY(frimware)
ADD_SUBDIRECTORY(player-driver)

