
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "ballistic_ode/BallisticSystem.h"
#include <vector>

using Catch::Approx;

TEST_CASE("BallisticSystem basic functionality", "[ballistic_system]") {
    SECTION("Constructor initializes parameters correctly") {
        double k = 0.1;
        double g = 9.81;
        BallisticSystem system(k, g);
        
        // Test that the system can be created without throwing
        REQUIRE_NOTHROW(BallisticSystem(k, g));
    }
    
    SECTION("Operator() computes derivatives correctly") {
        double k = 0.1;
        double g = 9.81;
        BallisticSystem system(k, g);
        
        // Initial state: position (0,0,10), velocity (10,0,0)
        std::vector<double> state = {0.0, 0.0, 10.0, 10.0, 0.0, 0.0};
        std::vector<double> derivatives(6);
        
        system(state, derivatives, 0.0);
        
        // Check velocity derivatives (should equal velocity)
        REQUIRE(derivatives[0] == Approx(10.0));  // dx/dt = vx
        REQUIRE(derivatives[1] == Approx(0.0));   // dy/dt = vy
        REQUIRE(derivatives[2] == Approx(0.0));   // dz/dt = vz
        
        // Check acceleration derivatives
        // dvx/dt should include drag
        REQUIRE(derivatives[3] < 0.0);  // Drag opposes motion
        REQUIRE(derivatives[4] == Approx(0.0));   // No y-component
        REQUIRE(derivatives[5] == Approx(-g));    // Gravity
    }
    
    SECTION("Zero velocity results in only gravitational acceleration") {
        double k = 0.1;
        double g = 9.81;
        BallisticSystem system(k, g);
        
        // State with zero velocity
        std::vector<double> state = {0.0, 0.0, 10.0, 0.0, 0.0, 0.0};
        std::vector<double> derivatives(6);
        
        system(state, derivatives, 0.0);
        
        // Velocity derivatives should be zero
        REQUIRE(derivatives[0] == Approx(0.0));
        REQUIRE(derivatives[1] == Approx(0.0));
        REQUIRE(derivatives[2] == Approx(0.0));
        
        // Acceleration should only be gravity
        REQUIRE(derivatives[3] == Approx(0.0));
        REQUIRE(derivatives[4] == Approx(0.0));
        REQUIRE(derivatives[5] == Approx(-g));
    }
}
