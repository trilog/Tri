cmake_minimum_required (VERSION 2.8)
set (PROJECT_NAME CandyKingTest)
Project (${PROJECT_NAME})

set (PROJECT_SOURCES CandyKing/main.cxx)

set (CANDYKING_SOURCES
    CandyKing/Animal.cxx
    CandyKing/Shepherd.cxx
    CandyKing/King.cxx
    CandyKing/OverGame.cxx
)

set (DBASE_SOURCES
    DBase/DDisplayManager.cxx
    DBase/DImage.cxx
    DBase/DSoundManager.cxx
    DBase/DText.cxx
    DBase/DTexture.cxx
    DBase/DTextureManager.cxx
    DBase/DTimer.cxx
    DBase/DWindow.cxx
    DBase/DFontManager.cxx
)

set (DGEOMETRY_SOURCES
    DGeometry/DLine.cxx
    DGeometry/DPoint.cxx
    DGeometry/DPolygon.cxx
)

set (SOURCES
    ${PROJECT_SOURCES}
    ${CANDYKING_SOURCES}
    ${DBASE_SOURCES}
    ${DGEOMETRY_SOURCES}
)

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set (CMAKE_DEBUG_POSTFIX _d)
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set (BUILD_POSTFIX "_d")
else (CMAKE_BUILD_TYPE STREQUAL Debug)
    set (BUILD_POSTFIX "")
endif (CMAKE_BUILD_TYPE STREQUAL Debug)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules")

find_Package (SDL2 REQUIRED)
find_Package (SDL2_image REQUIRED)
find_Package (SDL2_mixer REQUIRED)
find_Package (SDL2_ttf REQUIRED)

link_libraries (
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_MIXER_LIBRARY}
)

include_directories (
    ${CMAKE_SOURCE_DIR}/DBase
    ${CMAKE_SOURCE_DIR}/DGeometry
    ${CMAKE_SOURCE_DIR}/CandyKing
    ${SDL2_INCLUDE_DIR}
)

add_library (DBase SHARED ${DBASE_SOURCES})
add_library (DGeometry SHARED ${DGEOMETRY_SOURCES})
add_library (CandyKing SHARED ${CANDYKING_SOURCES})

file (COPY ${CMAKE_SOURCE_DIR}/Resources DESTINATION ${CMAKE_BINARY_DIR})

add_executable (${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCES})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_target_properties (${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}${BUILD_POSTFIX})
