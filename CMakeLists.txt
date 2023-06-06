cmake_minimum_required(VERSION 3.0.0)
project(PI-redes-sistemas-operativos-g1 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(PI-redes-sistemas-operativos-g1
    src/app/Database.cpp
    src/app/Database.hpp
    src/main.cpp
)

target_link_libraries(PI-redes-sistemas-operativos-g1
    sqlite3
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
