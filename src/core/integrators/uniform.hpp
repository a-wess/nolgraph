#ifndef _ONE_DIRECTIONAL_CLASS_
#define _ONE_DIRECTIONAL_CLASS_
#include "integrator.hpp"
#include <random>

class UniformRandomIntegrator: public Integrator {
public:
    UniformRandomIntegrator(int samples) : samples(samples) {
        std::random_device rd;
        gen = std::mt19937(rd());
        dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
    };
    vec3<float> render(const Scene& scene, const Ray& ray);
private:
    vec3<float> sample_hemishpere();
    vec3<float> sample_hemishpere(const vec3<float>& direction);
    vec3<float> trace_path(const Scene& scene, const Ray &primary_ray, int depth);
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;
    int samples;
};

#endif