#ifndef _RAYS_VEC4_
#define _RAYS_VEC4_

#include <cmath>
#include <iostream>

template <typename T> struct vec4 {
  T x, y, z, w;
  vec4() : x(0), y(0), z(0), w(0){};
  vec4(T _x, T _y, T _z, T _w) : x{_x}, y{_y}, z{_z}, w{_w} {};

  vec4<T> &operator-=(const vec4<T> &b) {
    this->x -= b.x;
    this->y -= b.y;
    this->z -= b.z;
    this->w -= b.w;
    return *this;
  };

  vec4<T> &operator+=(const vec4<T> &b) {
    this->x += b.x;
    this->y += b.y;
    this->z += b.z;
    this->w += b.w;
    return *this;
  };

  vec4<T> operator*(T scalar) const {
    return vec4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
  };
  vec4<T> &operator*=(T scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    this->w *= scalar;
    return *this;
  }

  vec4<T> operator/(T scalar) const {
    return vec4<T>(x / scalar, y / scalar, z / scalar, w / scalar);
  };
  vec4<T> &operator/=(T scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    this->w /= scalar;
    return *this;
  }

  T dot(const vec4<T> &b) const {
    return x * b.x + y * b.y + z * b.z + w * b.w;
  }

  T value() const { return sqrt(x * x + y * y + z * z + w * w); };

  vec4<T> norm() const {
    return vec4<T>(x / value(), y / value(), z / value(), w / value());
  };

  friend std::ostream &operator<<(std::ostream &os, const vec4<T> &v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
  };
};

template <typename T> vec4<T> operator*(T scalar, const vec4<T> &a) {
  return a * scalar;
}

template <typename T> vec4<T> operator+(const vec4<T> &a, const vec4<T> &b) {
  return vec4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

template <typename T> vec4<T> operator-(const vec4<T> &a, const vec4<T> &b) {
  return vec4<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

#endif
