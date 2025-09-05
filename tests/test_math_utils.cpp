
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "MathUtils.h"
#include <cmath>

using Catch::Approx;

TEST_CASE("find_bracket functionality", "[math_utils]") {
    
    SECTION("Finds bracket for sine function") {
        // Function: f(x) = sin(x), has root at x = π
        auto sine_func = [](double x) { return std::sin(x); };
        
        auto result = find_bracket(sine_func, 2.0, 4.0, 20);
        
        REQUIRE(result.has_value());
        // Should bracket the root at π ≈ 3.14159
        REQUIRE(result->first < M_PI);
        REQUIRE(result->second > M_PI);
    }
    
    SECTION("Returns nullopt when no bracket found") {
        // Function: f(x) = x^2 + 1, no real roots
        auto no_root_func = [](double x) { return x * x + 1.0; };
        
        auto result = find_bracket(no_root_func, -2.0, 2.0, 10);
        
        REQUIRE_FALSE(result.has_value());
    }

    SECTION("Returns nullopt for monotonic function without sign change") {
        // Function: f(x) = x + 5, always positive in range [0, 2]
        auto monotonic_func = [](double x) { return x + 5.0; };
        
        auto result = find_bracket(monotonic_func, 0.0, 2.0, 20);
        
        REQUIRE_FALSE(result.has_value());
    }
}
