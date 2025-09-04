
cmake_minimum_required(VERSION 3.15)
project(Ballistics CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost components provided by Conan
# Only request compiled components here.
# odeint is header-only and will be available via Boost::headers.
find_package(Boost REQUIRED COMPONENTS math)

# Add the include directory for your headers
include_directories(include)

# Define the executable and its source files
add_executable(ballistics
    src/main.cpp
    src/BallisticSystem.cpp
    src/BallisticUtils.cpp
    src/MathUtils.cpp
    src/TrajectoryCollector.cpp
)

# Link against the compiled math library and the header-only targets
target_link_libraries(ballistics PRIVATE Boost::math Boost::headers)
