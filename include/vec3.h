#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
    public: 
        double e[3];

        vec3() : e{0, 0, 0} {}
        vec3(double x, double y, double z) : e{x, y, z} {}
        
        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        double SquaredNorm() const {return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];}
        double norm() const {return std::sqrt(SquaredNorm());}

        vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
        double operator[](int i) const {return e[i];}
        double& operator[](int i) {return e[i];}

        vec3& operator+=(const vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(double t) {
            e[0] /= t;
            e[1] /= t;
            e[2] /= t;
            return *this;
        }
};

using point3 = vec3;

inline vec3 operator+(const vec3& vec1, const vec3& vec2) {
    return vec3(vec1[0] + vec2[0], vec1[1] + vec2[1], vec1[2] + vec2[2]);
}

inline vec3 operator-(const vec3& vec1, const vec3& vec2) {
    return vec3(vec1[0] - vec2[0], vec1[1] - vec2[1], vec1[2] - vec2[2]);
}

inline vec3 operator*(double t, const vec3& vec1) {
    return vec3(vec1[0] * t, vec1[1] *t, vec1[2] * t);
}

inline vec3 operator*(const vec3& vec1, const vec3& vec2) {
    return vec3(vec1[0] * vec2[0], vec1[1] * vec2[1], vec1[2] * vec2[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& vec1, double t) {
    return vec3(vec1[0] / t, vec1[1] / t, vec1[2] / t);
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.norm();
}

#endif