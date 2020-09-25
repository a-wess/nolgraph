#ifndef _CLASS_PLANE_
#define _CLASS_PLANE_
#include "../types.hpp"

class Plane : public ISurface {
public:
    Plane(const vec3<float>& position, const vec3<float>& normal, Material* material):
        position(position), normal(normal), material(material) {};
    Intersection intersect(const Ray& ray) {
        Intersection res;
        float t = - normal.dot(ray.origin - position) / normal.dot(ray.dir);
        if (t > 0) {
            res.hit = true;
            res.material = material;
            res.surface_normal = normal;
            res.position = ray.point_at(t);
            res.distance = (ray.dir * t).value();
        }
        return res;
    };
private:
    vec3<float> position;
    vec3<float> normal;
    Material* material;
};

#endif