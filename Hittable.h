#ifndef HITTABLE_H
#define HITTABLE_H

#include"Ray.h"
#include"RtWeekend.h"

class Material;

struct HitRecord {
    Point3 p;
    Vec3 normal;
    shared_ptr<Material> mat_ptr;
    double t;
    // ceci permet de savoir si la normal et le ray sont de meme sens ou de sens oppose.
    // donc de determiner ci la face est de l'interieur ou exterieur
    bool frontFace ; 
    inline void  SetFaceNormal(const Ray& r, const Vec3& outwardNormal){
        frontFace = dot(r.direction(), outwardNormal)<0;
        normal = frontFace? outwardNormal : -outwardNormal;
    }
};

class Hittable {
    public:
        virtual bool Hit(const Ray& r, double t_min,double t_max, HitRecord& rec) const =0;
};

#endif