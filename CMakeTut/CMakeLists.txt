cmake_minimum_required(VERSION 3.17)

project(cmake-tut)

include_directories(include)

add_executable(cmake-tut main.cpp)

if(PLATFORM_PSP)
    create_pbp_file(
        TARGET cmake-tut
        ICON_PATH NULL
        PREVIEW_PATH NULL
        TITLE cmake-tut
        BUILD_PRX
    )

    target_link_libraries(cmake-tut pspdebug pspdisplay pspge) 
endif()