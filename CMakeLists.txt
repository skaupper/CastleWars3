CMAKE_MINIMUM_REQUIRED (VERSION 2.8.0)
PROJECT (CastleWars)

OPTION (ENABLE_TESTS "Set to TRUE if you want to run the testcases afterwards" FALSE)
SET (GMOCK_SOURCE "/usr/src/gmock/gmock-all.cc" CACHE STRING "Path to the gmock-all.cc")
SET (GMOCK_LIBS "" CACHE STRING "Path to the GMock libs")

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
SET (CMAKE_CXX_STANDARD 14)

FIND_PACKAGE (SDL2 REQUIRED)
FIND_PACKAGE (SDL2_image REQUIRED)
FIND_PACKAGE (SDL2_ttf REQUIRED)
FIND_PACKAGE (SDL2_mixer REQUIRED)
FIND_PACKAGE (Jsoncpp REQUIRED)

INCLUDE_DIRECTORIES (include/
                     ${SDL2_INCLUDE_DIR}
                     ${SDL2_IMAGE_INCLUDE_DIR}
                     ${SDL2_TTF_INCLUDE_DIR}
                     ${SDL2_MIXER_INCLUDE_DIRS}
                     ${JSONCPP_INCLUDE_DIRS})

SET (LIBS ${SDL2_LIBRARY}
              ${SDL2_IMAGE_LIBRARIES}
              ${SDL2_TTF_LIBRARIES}
              ${SDL2_MIXER_LIBRARIES}
              ${JSONCPP_LIBRARIES})

SET(SOURCES src/main.cpp
            src/CastleWars.cpp
            src/Credits.cpp
            src/MainMenu.cpp
            src/Options.cpp
            src/OptionStorage.cpp)

# compile executable
ADD_EXECUTABLE(CastleWars ${SOURCES})
TARGET_LINK_LIBRARIES (CastleWars ${LIBS} bkengine)

# install target
SET (CMAKE_INSTALL_PREFIX ${CastleWars_SOURCE_DIR})
INSTALL (TARGETS CastleWars DESTINATION bin)
INSTALL (DIRECTORY res/ DESTINATION bin)
