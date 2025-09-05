
#pragma once
#include "MathUtils.h"
#include <vector>
#include <optional>
#include <entt/entt.hpp>

struct PositionComponent {
    Vector3 position;
};

struct VelocityComponent {
    Vector3 velocity;
};

struct ProjectileComponent {
    double mass;
    double drag_coefficient;
    double diameter;
    double initial_speed;
    double drag_patameter;
};

struct TargetComponent {
    entt::entity target_entity;
};
