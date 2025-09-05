#define _USE_MATH_DEFINES
#include "MathUtils.h"
#include "BallisticUtils.h"
#include "Constants.h"
#include "ecs/ECSManager.h"
#include <boost/math/tools/toms748_solve.hpp>
#include <iostream>
#include <cmath>
#include <utility>
#include <limits>
#include <optional>

int main() {
    ECSManager ecs_manager;
    double sx, sy, sz;
    double tx, ty, tz;

    std::cout << "Enter shooter position in the format \"x y z\": ";
    std::cin >> sx >> sy >> sz;

    std::cout << "Enter target position in the format \"x y z\": ";
    std::cin >> tx >> ty >> tz;

    auto target = ecs_manager.create_target(Vector3(tx, ty, tz));

    double mass;
    double initial_speed;
    double simulation_dt;
    std::cout << "Enter bullet mass in kg (e.g., 0.009 for 9mm): ";
    std::cin >> mass;
    std::cout << "Enter initial speed in m/s (e.g., 360): ";
    std::cin >> initial_speed;
    std::cout << "Enter simulation time step in seconds (e.g., 0.01): ";
    std::cin >> simulation_dt;

    auto shooter = ecs_manager.create_shooter(Vector3(sx, sy, sz), target, mass, initial_speed);
    
    std::cout << "\nCalculating optimal shooting angles..." << std::endl;
    ecs_manager.print_shooting_angles();

    return 0;
}