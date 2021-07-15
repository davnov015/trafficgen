cmake_minimum_required(VERSION 3.17)
project(trafficgen)

set(CMAKE_CXX_STANDARD 20)

add_executable(trafficgen main.cpp UDPSocket.cpp SocketHandle.cpp Common.cpp typedefs.h TrafficGen.cpp TrafficGen.h SmartLock.cpp SpinLock.cpp)
target_link_libraries(trafficgen -lpthread)