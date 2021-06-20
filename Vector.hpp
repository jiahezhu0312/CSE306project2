#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class Vector {
    public:
        explicit Vector(double x = 0., double y = 0., double z= 0.){
        e[0] = x;
        e[1] = y;
        e[2] = z;
    };

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        Vector operator-() const { return Vector(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        Vector& operator+=(const Vector &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vector& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vector& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        Vector assign(int index, double value){
            double x, y, z;
              if (index ==0){
                    x = value;
                    y = e[1];
                    z = e[2];
                }else if(index == 1){
                    x = e[0];
                    z = e[2];
                    y = value;
                }else if(index == 2){
                    x = e[0];
                    y = e[1];
                    z = value;
                };
            return Vector(x, y, z);

        }

    public:
        double e[3];
};

// Type aliases for Vector
using point3 = Vector;   // 3D point
using color = Vector;    // RGB color


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream &out, const Vector &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vector operator+(const Vector &u, const Vector &v) {
    return Vector(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vector operator-(const Vector &u, const Vector &v) {
    return Vector(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vector operator*(const Vector &u, const Vector &v) {
    return Vector(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vector operator*(double t, const Vector &v) {
    return Vector(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vector operator*(const Vector &v, double t) {
    return t * v;
}

inline Vector operator/(Vector v, double t) {
    return (1/t) * v;
}

inline double dot(const Vector &u, const Vector &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline Vector cross(const Vector &u, const Vector &v) {
    return Vector(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vector unit_vector(Vector v) {
    return v / v.length();
}

#endif
