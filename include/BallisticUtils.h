#pragma once
#include <vector>
#include "MathUtils.h"

double get_z_at_target_distance(Vector2 target, double angle, double k, double speed, double dt);
Vector2 project_target(const Vector3& shooter, const Vector3& target);