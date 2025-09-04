#include "BallisticUtils.h"
#include "BallisticSystem.h"
#include "TrajectoryCollector.h"
#include "Constants.h"
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