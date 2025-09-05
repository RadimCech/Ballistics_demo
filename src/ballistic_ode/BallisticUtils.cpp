#include "BallisticUtils.h"
#include "ballistic_ode/BallisticSystem.h"
#include "ballistic_ode/TrajectoryCollector.h"
#include "Constants.h"
#include "MathUtils.h"
#include <boost/numeric/odeint.hpp>
#include <limits>
#include <cmath>

Vector2 project_target(const Vector3& shooter, const Vector3& target) {
    Vector3 translation = target - shooter;
    return Vector2(Vector2(translation.x, translation.y).length(), translation.z);
}

double get_z_at_target_distance(Vector2 target, double angle, double k, double speed, double dt) {
    // Time settings
    const double t_start = Constants::SIMULATION_T_START;
    const double t_end = Constants::SIMULATION_T_END;

    // Initial conditions
    state_type state = {
        0.0,                       // u
        speed * std::cos(angle),   // vu
        0.0,                       // z
        speed * std::sin(angle)    // vz
    };

    BallisticSystem system(k);
    double z_at_target = std::numeric_limits<double>::lowest();
    TrajectoryCollector collector(target.x, z_at_target);

    // Integration
    boost::numeric::odeint::runge_kutta4<state_type> stepper;
    boost::numeric::odeint::integrate_const(
        stepper,
        system,
        state,
        t_start,
        t_end,
        dt,
        collector
    );

    return z_at_target;
}

std::optional<double> find_optimal_angle(const Vector3& shooter, const Vector3& target, 
                                        double mass, double initial_speed, double simulation_dt) {
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
        return angle_solution;
    }
    
    return std::nullopt;
}