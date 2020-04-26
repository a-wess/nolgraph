#ifndef _RAYS_VEC2_
#define _RAYS_VEC2_

#include <cmath>
#include <iostream>

template<typename T>
struct vec2 {
  T x, y;
  vec2(): x(0), y(0){};
  vec2(T _x, T _y): x{_x}, y{_y} {};

  vec2<T>& operator-=(const vec2<T>& b) {
    this->x -= b.x;
    this->y -= b.y;
    return *this;
  };

  vec2<T>& operator+=(const vec2<T>& b) {
    this->x += b.x;
    this->y += b.y;
    return *this;
  };
  
  vec2<T> operator*(T scalar) const { return vec2<T>(x * scalar, y * scalar); };
  vec2<T>& operator*=(T scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
  }

  vec2<T> operator/(T scalar) const { return vec2<T>(x / scalar, y / scalar); };
  vec2<T>& operator/=(T scalar) {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
  }

  T dot(const vec2<T>& b) const { return x * b.x + y * b.y; }

  T value() const { return sqrt(x*x + y*y); };
  
  vec2<T> norm() const { return vec2<T>(x/value(), y/value()); };
  
  friend std::ostream& operator<<(std::ostream& os, const vec2<T>& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
  };
}; 

template <typename T>
vec2<T> operator*(T scalar, const vec2<T>& a) { return a * scalar; }

template <typename T>
vec2<T> operator+(const vec2<T>& a, const vec2<T>& b) {
  return vec2<T>(a.x + b.x, a.y + b.y);
}

template <typename T>
vec2<T> operator-(const vec2<T>& a, const vec2<T>& b) {
  return vec2<T>(a.x - b.x, a.y - b.y);
}

#endif
