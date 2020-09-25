#ifndef _MATH_HELPERS_
#define _MATH_HELPERS_

#include "vec3.hpp"

vec3<float> sample_hemishpere();
vec3<float> sample_hemishpere(const vec3<float>& direction);
inline float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
inline vec3<float> vec_in_direction(const vec3<float>& dir, float n) {
    return vec3<float>(dir.x >= 0.0 ? n : -n, dir.y >= 0.0 ? n : -n, dir.z >= 0.0 ? n : -n);
}
#endif