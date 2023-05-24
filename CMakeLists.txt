cmake_minimum_required(VERSION 3.0.0)
project(PI-redes-sistemas-operativos-g1 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(PI-redes-sistemas-operativos-g1
    src/main.cpp
    src/concurrent/ThreadPool.cpp
    src/concurrent/ThreadPool.hpp
    src/net/Socket.cpp
    src/net/Socket.hpp
    src/net/TcpServer.cpp
    src/net/TcpServer.hpp
    src/http/HttpServer.cpp
    src/http/HttpServer.hpp
    src/url/URL.cpp
    src/url/URL.hpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
