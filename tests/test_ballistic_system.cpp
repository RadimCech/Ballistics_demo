
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
        
        // Initial state: u=0, vu=10, z=10, vz=0 (4-element state vector)
        std::vector<double> state = {0.0, 10.0, 10.0, 0.0};
        std::vector<double> derivatives(4);
        
        system(state, derivatives, 0.0);
        
        // Check derivatives based on actual implementation
        REQUIRE(derivatives[0] == Approx(10.0));  // du/dt = vu
        REQUIRE(derivatives[1] < 0.0);            // dvu/dt = -k * r * vu 
        REQUIRE(derivatives[2] == Approx(0.0));   // dz/dt = vz
        REQUIRE(derivatives[3] == Approx(-g));    // dvz/dt = -k * r * vz - g
    }
    
    SECTION("Drag force calculation") {
        double k = 0.1;
        double g = 9.81;
        BallisticSystem system(k, g);
        
        // State with horizontal velocity: u=0, vu=10, z=0, vz=0
        std::vector<double> state = {0.0, 10.0, 0.0, 0.0};
        std::vector<double> derivatives(4);
        
        system(state, derivatives, 0.0);
        
        // Check that drag is proportional to velocity
        double expected_drag = -k * 10.0 * 10.0; // -k * r * vu where r = |vu|
        REQUIRE(derivatives[1] == Approx(expected_drag));
    }
}
