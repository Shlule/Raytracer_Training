#ifndef MATERIAL_H
#define MATERIAL_H

#include"RtWeekend.h"
#include"HittableList.h"

class Material{
    public:
        virtual bool Scatter(const Ray& r_in, const HitRecord& rec , Color& attenuation , Ray& scattered) const =0;
};

class Lambertian : public Material{
    public:
        Lambertian(const Color& a) : albedo(a){}

        virtual bool Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered)const override{
            Vec3 scatterDirection = rec.normal+RandomUnitVector();
            if(scatterDirection.nearZero())
            scatterDirection = rec.normal;
            scattered = Ray(rec.p, scatterDirection);
            attenuation = albedo;
            return true;
        }
    public:
        Color albedo;
};
class Metal : public Material{
    public:
        Metal(const Color& a) : albedo(a){}
        virtual bool Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered)const override{
            Vec3 reflected= reflect(UnitVector(r_in.direction()),rec.normal);
            scattered = Ray(rec.p,reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal)> 0);
    }
    public:
        Color albedo;
};

#endif