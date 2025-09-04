#pragma once
#include <vector>
#include "BallisticSystem.h"

class TrajectoryCollector {
public:
    TrajectoryCollector(double targetU, double& z_out);
    void operator()(const state_type& state, double t);

private:
    double targetU_;
    double& z_at_target_;
    bool found_ = false;
    double u1_ = 0;
    double z1_ = 0;
};