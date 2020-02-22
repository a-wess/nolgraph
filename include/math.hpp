#pragma once
#include <cmath>

template<typename T>
class vec3 {
public:
  T x, y, z;
  vec3(): x(0), y(0), z(0){};
  vec3(T _x, T _y, T _z): x{_x}, y{_y}, z{_z}{};
  vec3<T> operator+(const vec3<T>& b) {
    return vec3<T>(x + b.x, y + b.y, z + b.z);
  };
  vec3<T> operator-(const vec3<T>& b) {
    return vec3<T>(x - b.x, y - b.y, z - b.z);
  };
  vec3<T> operator*(T scalar) { return vec3<T>(x * scalar, y * scalar, z * scalar); };
  T dot(const vec3<T>& b) { return x * b.x + y * b.y + z * b.z; }
  vec3<T> cross(const vec3<T>& b) {
    return vec3<T>(
                   y * b.z - b.y * z,
                   x * b.z - b.x * z,
                   x * b.y - b.x * y
                   );
  };
  T value() { return sqrt(x*x + y*y + z*z); };
  vec3<T> norm() { return vec3<T>(x/value(), y/value(), z/value()); } 
}; 
