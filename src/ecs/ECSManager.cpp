
#include "ECSManager.h"
#include "Constants.h"
#include <iostream>

ECSManager::ECSManager() {
    shooting_angle_system_ = std::make_unique<ShootingAngleSystem>(registry_);
}

entt::entity ECSManager::create_target(const Vector3& position) {
    auto entity = registry_.create();
    registry_.emplace<PositionComponent>(entity, position);
    return entity;
}

entt::entity ECSManager::create_shooter(const Vector3& position, entt::entity target_entity,
                                       double mass, double initial_speed) {
    auto entity = registry_.create();
    
    registry_.emplace<PositionComponent>(entity, position);
    registry_.emplace<ProjectileComponent>(entity, mass, 
                                          Constants::DEFAULT_DRAG_COEFFICIENT,
                                          Constants::DEFAULT_BULLET_DIAMETER,
                                          initial_speed);
    
    // Store reference to target entity
    if (registry_.valid(target_entity) && registry_.all_of<PositionComponent>(target_entity)) {
        registry_.emplace<TargetComponent>(entity, target_entity);
    }
    
    return entity;
}

void ECSManager::print_shooting_angles() {
    shooting_angle_system_->print_shooting_angles();
}
