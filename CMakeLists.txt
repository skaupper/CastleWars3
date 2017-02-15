CMAKE_MINIMUM_REQUIRED (VERSION 2.8.0)
PROJECT (CastleWars)

OPTION (ENABLE_TESTS "Set to TRUE if you want to run the testcases afterwards" FALSE)
SET (GMOCK_SOURCE "/usr/src/gmock/gmock-all.cc" CACHE STRING "Path to the gmock-all.cc")
SET (GMOCK_LIBS "" CACHE STRING "Path to the GMock libs")

SET (CMAKE_CXX_STANDARD 14)

ADD_SUBDIRECTORY (bkengine)

SET(SOURCES src/main.cpp)

# compile executable
ADD_EXECUTABLE(CastleWars ${SOURCES})
TARGET_LINK_LIBRARIES (CastleWars bkengine)

# install target
SET (CMAKE_INSTALL_PREFIX ${CastleWars_SOURCE_DIR})
INSTALL (TARGETS CastleWars DESTINATION bin)
INSTALL (DIRECTORY res/ DESTINATION bin)
