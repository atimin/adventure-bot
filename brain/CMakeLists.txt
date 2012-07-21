#----------------------------------
# Driver for the Player server
#----------------------------------

SET (CMAKE_MODULE_PATH "@CMAKE_INSTALL_PREFIX@/share/cmake/Modules")

INCLUDE (UsePlayerC)

PLAYER_ADD_PLAYERC_CLIENT (brain SOURCES brain.c LINKFLAGS ${replaceLib})


