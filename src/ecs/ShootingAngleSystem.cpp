
#include "ShootingAngleSystem.h"
#include "Constants.h"
#include "BallisticUtils.h"
#include <cmath>
#include <iostream>

ShootingAngleSystem::ShootingAngleSystem(entt::registry& registry) : registry_(registry) {}

void ShootingAngleSystem::print_shooting_angles() {
    auto view = registry_.view<PositionComponent, ProjectileComponent, TargetComponent>();
    
    for (auto entity : view) {
        auto& position = view.get<PositionComponent>(entity);
        auto& target_comp = view.get<TargetComponent>(entity);
        auto& projectile = view.get<ProjectileComponent>(entity);
        
        if (!registry_.valid(target_comp.target_entity) || 
            !registry_.all_of<PositionComponent>(target_comp.target_entity)) {
            std::cout << "Shooter Entity " << static_cast<uint32_t>(entity) 
                      << ": Invalid target entity" << std::endl;
            continue;
        }
        
        auto& target_position = registry_.get<PositionComponent>(target_comp.target_entity).position;
        
        std::cout << "Shooter Entity " << static_cast<uint32_t>(entity) << ":" << std::endl;
        std::cout << "  Position: (" << position.position.x << ", " 
                  << position.position.y << ", " << position.position.z << ")" << std::endl;
        std::cout << "  Target: (" << target_position.x << ", " 
                  << target_position.y << ", " << target_position.z << ")" << std::endl;
        
        auto optimal_angle = find_optimal_angle(position.position, target_position, 
                                               projectile.mass, projectile.initial_speed, 0.01);
        
        if (optimal_angle) {
            double degrees = optimal_angle.value() * 180.0 / M_PI;
            std::cout << "  Optimal Angle: " << degrees << " degrees" << std::endl;
        } else {
            std::cout << "  Optimal Angle: No valid trajectory found" << std::endl;
        }
        std::cout << std::endl;
    }
}
