#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include"Hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable{
    public:
        HittableList(){}
        HittableList(shared_ptr<Hittable> object) { add(object);}

        void clear() {objects.clear();}
        void add (shared_ptr<Hittable> object){objects.push_back(object);}

        virtual bool Hit(const Ray& r , double t_min, double t_max, HitRecord& rec) const override;

        std::vector<shared_ptr<Hittable>> objects;
};

bool HittableList::Hit(const Ray& r , double t_min, double t_max, HitRecord& rec) const {
    HitRecord tempRec;
    bool hitAnything=false;
    double ClosestSoFar = t_max;
    // ceci est la declaration d'un for each
    for(const shared_ptr<Hittable>& object : objects){
        if(object->Hit(r,t_min,ClosestSoFar,tempRec)){
            hitAnything = true;
            ClosestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}

#endif