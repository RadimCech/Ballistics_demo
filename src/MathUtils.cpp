#include "MathUtils.h"

std::optional<std::pair<double, double>> find_bracket(
    const std::function<double(double)>& func,
    double min_x,
    double max_x,
    int steps
) {
    const double step_size = (max_x - min_x) / steps;
    const double mid_x = (min_x + max_x) / 2.0;

    double best_x = mid_x;
    double best_fx = func(best_x);

    for (int i = 1; i <= steps; i++) {
        int sign = (i % 2 == 0) ? 1 : -1;
        double new_x = mid_x + sign * i * step_size;
        double new_fx = func(new_x);

        if (best_fx * new_fx < 0) {
            if (best_x < new_x) {
                return std::make_pair(best_x, new_x);
            }
            else {
                return std::make_pair(new_x, best_x);
            }
        }

        if (std::abs(new_fx) < std::abs(best_fx)) {
            best_x = new_x;
            best_fx = new_fx;
        }
    }

    return std::nullopt;
}