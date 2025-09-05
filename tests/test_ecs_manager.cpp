
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "ecs/ECSManager.h"
#include "ecs/Components.h"
#include <iostream>
#include <sstream>

TEST_CASE("ECSManager functionality", "[ecs_manager]") {
    SECTION("Constructor creates manager successfully") {
        REQUIRE_NOTHROW(ECSManager());
    }
    
    SECTION("Create target entity") {
        ECSManager manager;
        Vector3 position{10.0, 20.0, 30.0};
        
        auto target = manager.create_target(position);
        
        // Entity should be valid
        REQUIRE(target != entt::null);
    }
    
    SECTION("Create shooter entity") {
        ECSManager manager;
        Vector3 target_pos{100.0, 0.0, 0.0};
        Vector3 shooter_pos{0.0, 0.0, 0.0};
        
        auto target = manager.create_target(target_pos);
        auto shooter = manager.create_shooter(shooter_pos, target, 1.0, 100.0);
        
        // Both entities should be valid
        REQUIRE(target != entt::null);
        REQUIRE(shooter != entt::null);
        REQUIRE(shooter != target);
    }
    
    SECTION("Print shooting angles doesn't crash") {
        ECSManager manager;
        Vector3 target_pos{100.0, 0.0, 0.0};
        Vector3 shooter_pos{0.0, 0.0, 0.0};
        
        auto target = manager.create_target(target_pos);
        auto shooter = manager.create_shooter(shooter_pos, target, 1.0, 100.0);
        
        // Redirect cout to capture output
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
        
        REQUIRE_NOTHROW(manager.print_shooting_angles());
        
        // Restore cout
        std::cout.rdbuf(old);
        
        // Should have produced some output
        REQUIRE(!buffer.str().empty());
    }
}
