cmake_minimum_required(VERSION 3.31)
project(SpartanoidLib)

set(SOURCE_FILES
        pch.h
        MainFrame.cpp
        MainFrame.h
        ScoreBoard.cpp
        ScoreBoard.h
        SpartanoidView.cpp
        SpartanoidView.h
        Spartanoid.cpp
        Spartanoid.h
        Item.cpp
        Item.h
        Paddle.cpp
        Paddle.h
        Ball.cpp
        Ball.h
        ids.h
        Level.cpp
        Level.h
        Brick.cpp
        Brick.h
        Vector.cpp
        Vector.h
        Background.cpp
        Background.h
        PowerUp.cpp
        PowerUp.h
        Coin.cpp
        Coin.h
        Enemy.cpp
        Enemy.h
        ItemVisitor.h
        BallOutVisitor.cpp
        BallOutVisitor.h
        BrickExistsVisitor.cpp
        BrickExistsVisitor.h

)


set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

file(GLOB_RECURSE IMAGE_FILES "${CMAKE_SOURCE_DIR}/images/*")

foreach(file ${IMAGE_FILES})
    file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR} ${file})
    configure_file(${file} ${CMAKE_BINARY_DIR}/${rel_path} COPYONLY)
endforeach()