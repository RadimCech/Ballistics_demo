
#pragma once
#include <entt/entt.hpp>
#include "Components.h"
#include "ShootingAngleSystem.h"
#include <memory>

class ECSManager {
public:
    ECSManager();
    
    
    entt::entity create_target(const Vector3& position);
    
    entt::entity create_shooter(const Vector3& position, entt::entity target_entity,
                               double mass, double initial_speed);
    void print_shooting_angles();
    
private:
    entt::registry registry_;
    std::unique_ptr<ShootingAngleSystem> shooting_angle_system_;
};
