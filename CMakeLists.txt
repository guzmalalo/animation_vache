cmake_minimum_required(VERSION 3.30)
project(animation_vache C)

set(CMAKE_C_STANDARD 11)

add_executable(animation_vache main.c)

IF (WIN32)
    target_link_libraries(animation_vache -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE ()
    INCLUDE_DIRECTORIES(/usr/local/Cellar/allegro/5.2.10.1_1/include)
    LINK_DIRECTORIES(/usr/local/Cellar/allegro/5.2.10.1_1/lib)
    file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.10.1_1/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(animation_vache ${LIBRARIES})
ENDIF (WIN32)