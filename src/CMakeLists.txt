set(publicHeaders
        ${PROJECT_SOURCE_DIR}/include
)


set(SOURCES
        RobotController.cpp
        SpheroRobot.cpp
        ImguiIntfac.cpp
        ObstacleWarnings.cpp

)
#  TextHandles.cpp)

add_library(threeeeeppppSimulationLib ${SOURCES})
target_include_directories(threeeeeppppSimulationLib PUBLIC ${publicHeaders})
target_link_libraries(threeeeeppppSimulationLib PUBLIC threepp::threepp)