CMAKE_MINIMUM_REQUIRED (VERSION 2.8.0)
PROJECT (CastleWars)

OPTION (ENABLE_TESTS "Set to TRUE if you want to run the testcases afterwards" FALSE)
SET (GMOCK_SOURCE "/usr/src/gmock/gmock-all.cc" CACHE STRING "Path to the gmock-all.cc")
SET (GMOCK_LIBS "" CACHE STRING "Path to the GMock libs")

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CastleWars_SOURCE_DIR}/cmake)
SET (CMAKE_CXX_STANDARD 14)

FIND_PACKAGE (SDL2 REQUIRED)
FIND_PACKAGE (SDL2_image REQUIRED)
FIND_PACKAGE (SDL2_ttf REQUIRED)
FIND_PACKAGE (SDL2_mixer REQUIRED)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${SDL2_MIXER_INCLUDE_DIRS})


SET (SDL_LIBS ${SDL2_LIBRARY}
              ${SDL2_IMAGE_LIBRARIES}
              ${SDL2_TTF_LIBRARIES}
              ${SDL2_MIXER_LIBRARIES})

SET(SOURCES src/main.cpp)

SET(LIB_SOURCES src/Core.cpp
                src/Game.cpp
                src/Timer.cpp
                src/Scene.cpp
                src/Element.cpp
                src/Animation.cpp
                src/Texture.cpp
                src/Scene.cpp
                src/Logger.cpp)

IF(ENABLE_TESTS)
    SET (TEST_SOURCES test/main.cpp
                      test/CoreTest.cpp
                      test/TextureTest.cpp)
    SET (LIB_TEST_SOURCES src/SDLTemplates.cpp src/SDLWrapper.cpp)
    SET (LIB_SOURCES ${LIB_SOURCES} ${LIB_TEST_SOURCES})
    IF (NOT GMOCK_LIBS)
        SET (TEST_SOURCES ${TEST_SOURCES} "${GMOCK_SOURCE}")
    ENDIF ()

    ENABLE_TESTING()
    FIND_PACKAGE(GTest REQUIRED)
ENDIF()



# compile library
ADD_LIBRARY (bkengine STATIC ${LIB_SOURCES})
TARGET_INCLUDE_DIRECTORIES (bkengine PUBLIC include/)
TARGET_LINK_LIBRARIES (bkengine ${SDL_LIBS})

# compile executable
ADD_EXECUTABLE(CastleWars ${SOURCES})
TARGET_LINK_LIBRARIES (CastleWars bkengine)


IF(${ENABLE_TESTS})
    TARGET_COMPILE_DEFINITIONS(bkengine PRIVATE TEST)

    # compile test
    ADD_EXECUTABLE (CastleWarsTests ${TEST_SOURCES})
    TARGET_INCLUDE_DIRECTORIES (CastleWarsTests PRIVATE /usr/src/gmock /usr/src)
    TARGET_LINK_LIBRARIES (CastleWarsTests bkengine pthread ${GTEST_BOTH_LIBRARIES})
    IF (GMOCK_LIBS)
        TARGET_LINK_LIBRARIES (CastleWarsTests ${GMOCK_LIBS})
    ENDIF ()
    ADD_TEST (NAME Tests COMMAND CastleWarsTests)
ENDIF()



# install target
SET (CMAKE_INSTALL_PREFIX ${CastleWars_SOURCE_DIR})
INSTALL (TARGETS CastleWars DESTINATION bin)
INSTALL (DIRECTORY res/ DESTINATION bin)
