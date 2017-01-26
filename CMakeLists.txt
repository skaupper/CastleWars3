CMAKE_MINIMUM_REQUIRED (VERSION 3.0.0)
PROJECT (CastleWars)

ENABLE_TESTING()
FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTest_INCLUDE_DIR})

SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CastleWars_SOURCE_DIR}/cmake)

FIND_PACKAGE (SDL2 REQUIRED)
FIND_PACKAGE (SDL2_image REQUIRED)
FIND_PACKAGE (SDL2_ttf REQUIRED)
FIND_PACKAGE (SDL2_mixer REQUIRED)

SET(SOURCES src/main.cpp)

SET(LIB_SOURCES src/Core.cpp
                src/Game.cpp
                src/Timer.cpp
                src/Scene.cpp
                src/Element.cpp
                src/Animation.cpp
                src/Texture.cpp
                src/Scene.cpp
                src/SDLWrapper.cpp)

SET (LIB_LIBS ${SDL2_LIBRARY}
              ${SDL2_IMAGE_LIBRARIES}
              ${SDL2_TTF_LIBRARIES}
              ${SDL2_MIXER_LIBRARIES})

SET (TEST_SOURCES test/main.cpp
                  test/CoreTest.cpp)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${SDL2_MIXER_INCLUDE_DIRS}
                    include/)

SET (CMAKE_CXX_STANDARD 14)

ADD_DEFINITIONS(-DTEST)

ADD_LIBRARY (bkengine STATIC ${LIB_SOURCES})
TARGET_INCLUDE_DIRECTORIES (bkengine PUBLIC include/)

TARGET_LINK_LIBRARIES (bkengine ${LIB_LIBS})

ADD_EXECUTABLE(CastleWars ${SOURCES})
TARGET_LINK_LIBRARIES (CastleWars bkengine)

SET (CMAKE_INSTALL_PREFIX ${CastleWars_SOURCE_DIR})
INSTALL (TARGETS CastleWars DESTINATION bin )
INSTALL (DIRECTORY res/ DESTINATION bin )


ADD_EXECUTABLE (CastleWarsTests ${TEST_SOURCES})
TARGET_LINK_LIBRARIES (CastleWarsTests bkengine pthread gtest gmock gtest_main gmock_main)
ADD_TEST (NAME Tests COMMAND CastleWarsTests)
