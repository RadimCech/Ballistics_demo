#include "ballistic_ode/TrajectoryCollector.h"
#include "ballistic_ode/BallisticSystem.h"

TrajectoryCollector::TrajectoryCollector(double targetU, double& z_out)
    : targetU_(targetU), z_at_target_(z_out) {
}

void TrajectoryCollector::operator()(const state_type& state, double t) {
    if (found_) return;

    double u2 = state[0];
    double z2 = state[2];

    // interpolate
    if (u2 >= targetU_) {
        if (u2 != u1_) {
            z_at_target_ = z1_ + (targetU_ - u1_) * (z2 - z1_) / (u2 - u1_);
        }
        else {
            z_at_target_ = z2;
        }
        found_ = true;
    }
    u1_ = u2;
    z1_ = z2;
}