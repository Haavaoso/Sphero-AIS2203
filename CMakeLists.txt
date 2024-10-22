
cmake_minimum_required(VERSION 3.28)
project(SpheroSim)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
set(THREEPP_BUILD_TESTS OFF)
set(THREEPP_BUILD_EXAMPLES OFF)

find_package(imgui CONFIG REQUIRED)

find_package(glfw3 CONFIG REQUIRED)


#set(glfw3_DIR "C:/vcpkg/installed/x64-windows/share/glfw3")

add_subdirectory(src)

FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG 2e2397e0b7f0e639f254ea3046b70e53a71f0387
        #GIT_PROGRESS TRUE
)

#set(THREEPP_BUILD_GLFW OFF)
#set(THREEPP_BUILD_EXTERNAL OFF) # Disable external dependencies like glfw
set(THREEPP_USE_EXTERNAL_GLFW ON)
#set(THREEPP_BUILD_EXAMPLES OFF) # Just in case examples pull in glfw
#set(THREEPP_BUILD_TESTS OFF)    # Disable tests to avoid unwanted dependencies

FetchContent_MakeAvailable(threepp)

set(SIMPLE_SOCKET_BUILD_TESTS OFF)
FetchContent_Declare(
        SimpleSocket
        GIT_REPOSITORY https://github.com/markaren/SimpleSocket.git
        GIT_TAG e0e989bdd52137d743a4599e25167d5681a0de00
)
FetchContent_MakeAvailable(SimpleSocket)

set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.6.1")

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

add_executable(main main.cpp)

add_executable(SpheroSim
        src/main.cpp
        src/RobotController.cpp
        src/SpheroRobot.cpp
        src/ImguiIntfac.cpp
        src/ObstacleWarnings.cpp
)
add_executable(shees src/lidar.cpp)

set(SFML_DIR "C:/libs/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 REQUIRED COMPONENTS system window graphics network audio)

# Define a variable for the include directory
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

target_include_directories(main PUBLIC ${INCLUDE_DIR})
target_include_directories(SpheroSim PUBLIC ${INCLUDE_DIR})

target_link_libraries(main PUBLIC simple_socket)

target_link_libraries(SpheroSim PUBLIC threepp::threepp simple_socket imgui::imgui)

target_link_libraries(shees PUBLIC sfml-system sfml-window sfml-graphics)

add_custom_command(TARGET shees POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin"
        $<TARGET_FILE_DIR:shees>)

add_custom_command(TARGET SpheroSim POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin"
        $<TARGET_FILE_DIR:SpheroSim>)
