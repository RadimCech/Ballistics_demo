#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "ballistic_ode/TrajectoryCollector.h"
#include <vector>

using Catch::Approx;

TEST_CASE("TrajectoryCollector functionality", "[trajectory_collector]") {

    SECTION("Collector finds target crossing") {
        double targetU = 50.0;
        double z_out = 0.0;
        TrajectoryCollector collector(targetU, z_out);
        
        // Simulate trajectory points before target
        std::vector<double> state1 = {40.0, 0.0, 5.0, 10.0, 0.0, -2.0};
        collector(state1, 1.0);
        
        // Simulate trajectory point after target
        std::vector<double> state2 = {60.0, 0.0, 3.0, 10.0, 0.0, -2.0};
        collector(state2, 2.0);
        
        // z_out should be interpolated between the two points
        REQUIRE(z_out != 0.0);
        REQUIRE(z_out > 3.0);
        REQUIRE(z_out < 5.0);
    }
    
    SECTION("Collector handles exact target hit") {
        double targetU = 50.0;
        double z_out = 0.0;
        TrajectoryCollector collector(targetU, z_out);
        
        // Exact hit at target
        std::vector<double> state = {50.0, 0.0, 4.0, 10.0, 0.0, -2.0};
        collector(state, 1.0);
        
        REQUIRE(z_out == Approx(4.0));
    }
}
