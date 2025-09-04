
#pragma once

#include <cmath>

namespace Constants {
    constexpr double GRAVITY = 9.81;
    constexpr double AIR_DENSITY = 1.225; // kg/m^3

    constexpr double DEFAULT_DRAG_COEFFICIENT = 0.30;
    constexpr double DEFAULT_BULLET_DIAMETER = 0.009; // 9mm

    constexpr double SIMULATION_T_START = 0.0;
    constexpr double SIMULATION_T_END = 5.0;


    constexpr double SOLVER_MIN_ANGLE_RAD = -M_PI * 0.5;
    constexpr double SOLVER_MAX_ANGLE_RAD = M_PI * 0.5;    
    constexpr int SOLVER_TOLERANCE_BITS = 30;
    constexpr int SOLVER_MAX_ITER = 100;
}
