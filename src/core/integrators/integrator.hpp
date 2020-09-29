#ifndef _INTEGRATOR_CLASS_
#define _INTEGRATOR_CLASS_
#include <core/scene.hpp>
#include <math/vec3.hpp>

class Integrator {
public:
    virtual vec3<float> render(const Scene& scene, const Ray& ray) = 0;
  virtual ~Integrator() = 0;
};

#endif