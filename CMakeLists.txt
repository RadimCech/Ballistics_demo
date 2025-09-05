
cmake_minimum_required(VERSION 3.15)
project(ballistics)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED)
find_package(EnTT REQUIRED)

include_directories(include)
include_directories(include/ballistic_ode)
include_directories(include/ecs)

set(SOURCES
    src/main.cpp
    src/MathUtils.cpp
    src/ballistic_ode/BallisticSystem.cpp
    src/ballistic_ode/BallisticUtils.cpp
    src/ballistic_ode/TrajectoryCollector.cpp
    src/ecs/ECSManager.cpp
    src/ecs/ShootingAngleSystem.cpp
)

add_executable(ballistics ${SOURCES})

target_link_libraries(ballistics 
    ${Boost_LIBRARIES}
    EnTT::EnTT
)
