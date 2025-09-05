
#pragma once
#include <entt/entt.hpp>
#include "Components.h"
#include "BallisticUtils.h"

class ShootingAngleSystem {
public:
    ShootingAngleSystem(entt::registry& registry);
    
    void print_shooting_angles();
    
private:
    entt::registry& registry_;
};
