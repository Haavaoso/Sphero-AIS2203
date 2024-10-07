cmake_minimum_required(VERSION 3.28)
project(SpheroSim)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
set(THREEPP_BUILD_TESTS OFF)
set(THREEPP_BUILD_EXAMPLES OFF)
FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG e3f61e4f93bbb3f3b64abe83d52cbfe6166df8e9
)
FetchContent_MakeAvailable(threepp)

set(SIMPLE_SOCKET_BUILD_TESTS OFF)
FetchContent_Declare(
        SimpleSocket
        GIT_REPOSITORY https://github.com/markaren/SimpleSocket.git
        GIT_TAG 13996f0f65d9294849e5044916ddc2a69edc5232
)
FetchContent_MakeAvailable(SimpleSocket)



add_executable(SpheroSim main.cpp)

target_link_libraries(SpheroSim PUBLIC threepp::threepp simple_socket)




