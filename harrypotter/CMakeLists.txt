cmake_minimum_required(VERSION 3.6)
project(Ghost)

set(CMAKE_CXX_STANDARD 98)

SET(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
SET(GCC_COVERAGE_LINK_FLAGS "-pthread")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )
set(SOURCE_FILES main.cpp
        Ghost/SmartGhost/SmartGhost.cpp
        Ghost/SmartGhost/SmartGhost.h
        Ghost/DummyGhost/DummyGhost.cpp
        Ghost/DummyGhost/DummyGhost.h
        Ghost/Ghost.h
        Move.h
        Coordinate/Coordinate.cpp
        Coordinate/Coordinate.h
        Map/Map.cpp
        Map/Map.h
        ObjectInfo/ObjectInfo.cpp
        ObjectInfo/ObjectInfo.h
        PlayerInfo/PlayerInfo.cpp
        PlayerInfo/PlayerInfo.h
        Player/Player.cpp
        Player/Player.h
        GhostInfo/GhostInfo.cpp
        GhostInfo/GhostInfo.h
        StupidPlayer/StupidPlayer.cpp
        StupidPlayer/StupidPlayer.h
        GameBoard/GameBoard.cpp
        GameBoard/GameBoard.h
        Errors/AllPlayersAreKilledException.h
        DisplaySystem/Window/Window.cpp
        DisplaySystem/Window/Window.h
        DisplaySystem/LeaderBoard/LeaderBoard.cpp
        DisplaySystem/LeaderBoard/LeaderBoard.h
        DisplaySystem/LogArea/LogArea.cpp
        DisplaySystem/LogArea/LogArea.h Defaults.h
        Utilities/FileReader.cpp
        Utilities/FileReader.h
        Utilities/Record.cpp
        Utilities/Record.h
        ManualPlayer/ManualPlayer.cpp
        ManualPlayer/ManualPlayer.h
        Ghost/SmartGhost/Graph/Graph.cpp
        Ghost/SmartGhost/Graph/Graph.h
        Ghost/Ghost.cpp
        DisplaySystem/InfoBoard/InfoBoard.h
        DisplaySystem/InfoBoard/InfoBoard.cpp
        DisplaySystem/InfoBoard/Info.h
        DisplaySystem/InfoBoard/Info.cpp
        Utilities/ArrayList.h
        Errors/IndexOutOfBoundsException.h)
add_executable(Ghost ${SOURCE_FILES})