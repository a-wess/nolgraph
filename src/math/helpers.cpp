#include "helpers.hpp"
#include <random>

vec3<float> sample_hemishpere() {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);
    float r1 = dis(gen);
    float r2 = dis(gen);
    float z = sqrt(1-r2);

    auto phi = 2*M_PI*r1;
    float x = cos(phi)*sqrt(r2);
    float y = sin(phi)*sqrt(r2);

    return vec3(x, y, z);
}

vec3<float> sample_hemishpere(const vec3<float>& direction) {
    vec3<float> u = std::abs(direction.x) > 0.9f ? vec3<float>(0.0f, 1.0f, 0.0f) : vec3<float>(1.0f, 0.0f, 0.0f);
    auto s = direction.cross(u).norm();
    auto t = s.cross(direction);
    auto sampled = sample_hemishpere();
    return sampled.x * s + sampled.y * t + sampled.z * direction;
}