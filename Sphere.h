#ifndef SPHERE_H
#define SPHERE_H

#include"Hittable.h"
#include"Vec3.h"

class Sphere : public Hittable {
    public:
        Sphere(){}
        Sphere(Point3 cen , double r ,shared_ptr<Material> m) : center(cen), radius(r), mat_ptr(m){}; 

        virtual bool Hit(const Ray& r , double t_min ,double t_max, HitRecord& rec) const override;
    public:
        Point3 center;
        double radius;
        shared_ptr<Material> mat_ptr;

};
// t_min et t_max permet de calculer  ci il y a contact dans une range donné
bool Sphere::Hit(const Ray& r , double t_min ,double t_max, HitRecord& rec) const{
    Vec3 oc = r.origin() - center;
    //definition des trois composante d'un polynome de second degres;
    double a = r.direction().lengthSquared();
    double halfB = dot(oc, r.direction());
    double c = oc.lengthSquared() - radius*radius;

    double discriminant = halfB*halfB - a*c;
    if( discriminant < 0) return false;
    double sqrtDiscriminant = sqrt(discriminant);

    // find the nearest root thet lies in the acceptable range.

    double root =(-halfB - sqrtDiscriminant) /a ;
    if(root < t_min || t_max < root){
        root=(- halfB + sqrtDiscriminant) /a;
        if(root < t_min || t_max < root)
            return false;
    }
    // c'est la racine du polynome
    rec.t =root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center)/ radius;
    Vec3 outWardNormal = (rec.p - center)/radius;
    rec.SetFaceNormal(r,outWardNormal);
    rec.mat_ptr =mat_ptr;

    return true;
}

#endif