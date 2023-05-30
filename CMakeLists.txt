cmake_minimum_required(VERSION 3.0.0)
project(PI-redes-sistemas-operativos-g1 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(PI-redes-sistemas-operativos-g1
    src/app/App.cpp
    src/app/App.hpp
    src/common/common.hpp
    src/common/Util.cpp
    src/common/Util.hpp
    src/concurrent/ThreadPool.cpp
    src/concurrent/ThreadPool.hpp
    src/http/HttpApp.cpp
    src/http/HttpApp.hpp
    src/http/HttpMessage.cpp
    src/http/HttpMessage.hpp
    src/http/HttpRequest.cpp
    src/http/HttpRequest.hpp
    src/http/HttpResponse.cpp
    src/http/HttpResponse.hpp
    src/http/HttpServer.cpp
    src/http/HttpServer.hpp
    src/menu/FSMenu.cpp
    src/menu/FSMenu.hpp
    src/net/SharedSocket.cpp
    src/net/SharedSocket.cpp
    src/net/Socket.cpp
    src/net/Socket.cpp
    src/net/TcpServer.cpp
    src/net/TcpServer.hpp
    src/url/URL.cpp
    src/url/URL.hpp
    src/authenticator.cpp
    src/authenticator.hpp
    src/error.hpp
    src/fs.cpp
    src/fs.hpp
    src/hash.cpp
    src/hash.hpp
    src/main.cpp
)

target_link_libraries(PI-redes-sistemas-operativos-g1
    crypto
    sqlite3
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
