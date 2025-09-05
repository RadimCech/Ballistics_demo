#include "ballistic_ode/BallisticSystem.h"
#include <cmath>

BallisticSystem::BallisticSystem(double k, double g) : k_(k), g_(g) {}

void BallisticSystem::operator()(const state_type& U, state_type& dUdt, double t) const {
    double u = U[0];   double vu = U[1];
    double z = U[2];   double vz = U[3];

    double r = std::sqrt(vu * vu + vz * vz);

    dUdt[0] = vu;                // du/dt   = vu
    dUdt[1] = -k_ * r * vu;      // dvu/dt  = -k * r * vu
    dUdt[2] = vz;                // dz/dt   = vz
    dUdt[3] = -k_ * r * vz - g_; // dvz/dt  = -k * r * vz - g
}