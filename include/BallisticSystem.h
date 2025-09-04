#pragma once
#include <vector>
#include "Constants.h"

// State vector: (u, vu, z, vz)
typedef std::vector<double> state_type;

// define the corresponding 1st order system as a functor
class BallisticSystem {
public:
    BallisticSystem(double k, double g = Constants::GRAVITY);
    void operator()(const state_type& X, state_type& dXdt, double t) const;

private:
    double k_;
    double g_;
};
