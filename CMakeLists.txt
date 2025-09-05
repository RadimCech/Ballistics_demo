
cmake_minimum_required(VERSION 3.15)
project(ballistics)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED COMPONENTS system)
find_package(EnTT REQUIRED)
find_package(Catch2 REQUIRED)

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

set(TEST_SOURCES
    tests/test_ballistic_system.cpp
    tests/test_trajectory_collector.cpp
    tests/test_ecs_manager.cpp
    tests/test_math_utils.cpp
    src/MathUtils.cpp
    src/ballistic_ode/BallisticSystem.cpp
    src/ballistic_ode/BallisticUtils.cpp
    src/ballistic_ode/TrajectoryCollector.cpp
    src/ecs/ECSManager.cpp
    src/ecs/ShootingAngleSystem.cpp
)

add_executable(ballistics_tests ${TEST_SOURCES})

target_link_libraries(ballistics_tests 
    Boost::system
    EnTT::EnTT
    Catch2::Catch2WithMain
)

enable_testing()
add_test(NAME ballistics_unit_tests COMMAND ballistics_tests)
