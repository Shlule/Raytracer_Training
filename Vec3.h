#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class Vec3 {
    // on recrer la classe vec3 comme on la connait
    public:
        Vec3() : e{0,0,0} {}
        Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        // permet d'inversé fonction
        Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
        // i doit etre compris entre 0 et 2 representant les coordonne x,y et z ddonc vec3[i] i = a 1 donc donne la valeur x du vecteur
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        Vec3& operator+=(const Vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(lengthSquared());
        }

        double lengthSquared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
        inline static Vec3 Random(){
            return Vec3 (RandomDouble(),RandomDouble(),RandomDouble());
        }
        inline static Vec3 Random(double min,double max){
            return Vec3(RandomDouble(min,max),RandomDouble(min,max),RandomDouble(min,max));
        }
        bool nearZero() const {
            //return true if the vector is close to 0 in all dimensions
            const double s = 1e-8;
            return(fabs(e[0])<s)&&(fabs(e[1])<s)&&(fabs(e[2])<s);
        }

    public:
        double e[3];
};
// Utility Function
// on va créer de surcharge operateur pour nous permettre de faire de operation avec des vecteur

// permet d'ajouter une vecteur dans un stream on fait ofstream& pour pouvoir iterret l'operation plusieur fois.
inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
// addition de deux vecteur
inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
// soustraction de deux vecteur // tres utile pour connaitre la distance entre deux objet.
inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
// une multiplication simple de toutes les coordonne de deux vecteur donc x ux*vx
inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
// multipliction d'un vecteur avec une valeur
inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}
// permet la commutativité dans le code
inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}
// produit saclaire de deux vecteur // si il est  =0 les deux vecteur sont perpendiculaire si = 1 parralele =-1 parrale mais oppsés.
inline double dot(const Vec3 &u, const Vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
// this function return les coordonne du vecteur unitaire. 
inline Vec3 UnitVector(Vec3 v) {
    return v / v.length();
}

// permet  de renvoyer le rayon dans une direction aleatoire controler  plus tard cela deviendra la Roughness
Vec3 RandomInUnitSphere()
{
    while(true){
        Vec3 p = Vec3::Random(-1,1);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}
//fait comme  RandomUnitInSphere mais renvoie un vecteur Unitaire.
Vec3 RandomUnitVector(){
    return UnitVector(RandomInUnitSphere());
}
// calcul les reflection parfaite d'un vecteur sur un angle;
Vec3 reflect(const Vec3& v, const Vec3& n){
    return v - 2*dot(v,n)*n;
}

// Type aliases for vec3
using Point3 = Vec3;   // 3D point
using Color = Vec3;    // RGB color

#endif