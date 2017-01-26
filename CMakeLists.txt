CMAKE_MINIMUM_REQUIRED (VERSION 3.0.0)
PROJECT (CastleWars)

SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CastleWars_SOURCE_DIR}/cmake")

FIND_PACKAGE (SDL2 REQUIRED)
FIND_PACKAGE (SDL2_image REQUIRED)
FIND_PACKAGE (SDL2_ttf REQUIRED)
FIND_PACKAGE (SDL2_mixer REQUIRED)

# FILE (GLOB SOURCE src/*)
SET(SOURCES src/main.cpp
            src/Core.cpp
            src/Game.cpp
            src/Timer.cpp
            src/Scene.cpp
            src/Element.cpp
            src/Animation.cpp
            src/Texture.cpp
            src/Scene.cpp)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${SDL2_MIXER_INCLUDE_DIRS}
                    include/)

SET (CMAKE_CXX_STANDARD 14)

ADD_EXECUTABLE (CastleWars ${SOURCES})

TARGET_LINK_LIBRARIES (CastleWars ${SDL2_LIBRARY}
                                  ${SDL2_IMAGE_LIBRARIES}
                                  ${SDL2_TTF_LIBRARIES}
                                  ${SDL2_MIXER_LIBRARIES})
