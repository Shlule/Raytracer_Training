#ifndef RAY_H
#define RAY_H

#include"Vec3.h"

class Ray {
    public:
        Ray(){}
        Ray(const Point3& origin, Vec3& direction) : orig(origin) , dir(direction) {}

        // function that return a Vec3 corresponding to the origin of the Ray Point A
        Point3 origin() const {return orig;}
        // function that return the dirrection of the ray point B
        Vec3 direction() const {return dir;}
        // function that return  The pararmetrique equation of the vector.
        Point3 at(double t)const {
            return orig + (t*dir);
        }


        Point3 orig; 
        Vec3 dir;
   
        
};

#endif