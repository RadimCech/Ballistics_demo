
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "ecs/ECSManager.h"
#include "ecs/Components.h"
#include <iostream>
#include <sstream>

TEST_CASE("ECSManager functionality", "[ecs_manager]") {
    
    SECTION("Create target entity") {
        ECSManager manager;
        Vector3 position{10.0, 20.0, 30.0};
        
        auto target = manager.create_target(position);
        
        REQUIRE(target != static_cast<entt::entity>(entt::null));
    }
    
    SECTION("Create shooter entity") {
        ECSManager manager;
        Vector3 target_pos{100.0, 0.0, 0.0};
        Vector3 shooter_pos{0.0, 0.0, 0.0};
        
        auto target = manager.create_target(target_pos);
        auto shooter = manager.create_shooter(shooter_pos, target, 1.0, 100.0);
        
        REQUIRE(target != static_cast<entt::entity>(entt::null));
        REQUIRE(shooter != static_cast<entt::entity>(entt::null));
        REQUIRE(shooter != target);
    }
    
    SECTION("Print shooting angles doesn't crash") {
        ECSManager manager;
        Vector3 target_pos{100.0, 0.0, 0.0};
        Vector3 shooter_pos{0.0, 0.0, 0.0};
        
        auto target = manager.create_target(target_pos);
        auto shooter = manager.create_shooter(shooter_pos, target, 1.0, 100.0);
        
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
        
        REQUIRE_NOTHROW(manager.print_shooting_angles());
        
        std::cout.rdbuf(old);
        
        REQUIRE(!buffer.str().empty());
    }
}
