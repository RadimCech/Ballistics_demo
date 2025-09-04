#define _USE_MATH_DEFINES
#include "MathUtils.h"
#include "BallisticUtils.h"
#include "Constants.h"
#include <boost/math/tools/toms748_solve.hpp>
#include <iostream>
#include <cmath>
#include <utility>
#include <limits> 

int main() {
    double sx, sy, sz;
    double tx, ty, tz;

    std::cout << "Enter shooter position in the format \"x y z\": ";
    std::cin >> sx >> sy >> sz;

    std::cout << "Enter target position in the format \"x y z\": ";
    std::cin >> tx >> ty >> tz;

    Vector3 shooter(sx, sy, sz);
    Vector3 target(tx, ty, tz);

    double mass;
    double initial_speed;
    double simulation_dt;
    std::cout << "Enter bullet mass in kg (e.g., 0.009 for 9mm): ";
    std::cin >> mass;
    std::cout << "Enter initial speed in m/s (e.g., 360): ";
    std::cin >> initial_speed;
    std::cout << "Enter simulation time step in seconds (e.g., 0.01): ";
    std::cin >> simulation_dt;

    double Area = M_PI * pow(Constants::DEFAULT_BULLET_DIAMETER * 0.5, 2); // cross section area
    double k = 0.5 * Constants::AIR_DENSITY * Constants::DEFAULT_DRAG_COEFFICIENT * Area / mass;

    Vector2 target_plane = project_target(shooter, target);

    auto func = [&](double angle) {
        double z_at_target = get_z_at_target_distance(target_plane, angle, k, initial_speed, simulation_dt);
        return z_at_target - target_plane.y;
    };

    //func is not well behaved so we need bracketing
    auto bracket_result = find_bracket(func, Constants::SOLVER_MIN_ANGLE_RAD, Constants::SOLVER_MAX_ANGLE_RAD);

    if (bracket_result) {
        boost::uintmax_t max_iter = Constants::SOLVER_MAX_ITER;

        auto result = boost::math::tools::toms748_solve(
            func,
            bracket_result->first, bracket_result->second,
            boost::math::tools::eps_tolerance<double>(Constants::SOLVER_TOLERANCE_BITS),
            max_iter
        );

        double angle_solution = (result.first + result.second) / 2.0;
        double degrees = angle_solution * 180.0 / M_PI;

        std::cout << "\nOptimal launch angle: " << degrees << " degrees" << std::endl;

    }
    else {
        std::cerr << "\nCould not find a valid bracket for the root." << std::endl;
        std::cerr << "The target may be out of range for the given initial speed." << std::endl;
    }

    return 0;
}