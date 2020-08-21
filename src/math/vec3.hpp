#ifndef _RAYS_VEC3_
#define _RAYS_VEC3_

#include <cassert>
#include <cmath>
#include <iostream>

template <typename T> struct vec3 {
  T x, y, z;
  vec3() : x(0), y(0), z(0){};
  vec3(T _x, T _y, T _z) : x{_x}, y{_y}, z{_z} {};

  T operator[](int i) const {
    assert(i >= 0 && i < 3);
    return i == 0 ? x : i == 1 ? y : z;
  };

  vec3<T> &operator-=(const vec3<T> &b) {
    this->x -= b.x;
    this->y -= b.y;
    this->z -= b.z;
    return *this;
  };

  vec3<T> &operator+=(const vec3<T> &b) {
    this->x += b.x;
    this->y += b.y;
    this->z += b.z;
    return *this;
  };

  vec3<T> operator*(T scalar) const {
    return vec3<T>(x * scalar, y * scalar, z * scalar);
  };
  vec3<T> &operator*=(T scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
  }

  vec3<T> operator/(T scalar) const {
    return vec3<T>(x / scalar, y / scalar, z / scalar);
  };
  vec3<T> &operator/=(T scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
  }

  T dot(const vec3<T> &b) const { return x * b.x + y * b.y + z * b.z; }

  vec3<T> cross(const vec3<T> &b) const {
    return vec3<T>(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
  };

  T value() const { return sqrt(x * x + y * y + z * z); };

  vec3<T> norm() const {
    return vec3<T>(x / value(), y / value(), z / value());
  };

  bool operator==(const vec3<T> &b) const {
    return x == b.x && y == b.y && z == b.z;
  };

  friend std::ostream &operator<<(std::ostream &os, const vec3<T> &v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
  };
};

template <typename T> vec3<T> operator*(T scalar, const vec3<T> &a) {
  return a * scalar;
}

template <typename T> vec3<T> operator+(const vec3<T> &a, const vec3<T> &b) {
  return vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template <typename T> vec3<T> operator-(const vec3<T> &a, const vec3<T> &b) {
  return vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

#endif
