#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include<cmath>
#include<limits>
#include<memory>
#include<cstdlib>
#include<random>

//using

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//constans

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility function

inline double DegreesToRadiant(double degrees){
    return degrees * pi / 100.0;
}

inline double RandomDouble(){
    static std::uniform_real_distribution<double> distribution(0.0,1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
// inline double RandomDouble(){
//     //return a random real in [0,1]
//     return rand() / (RAND_MAX+1.0);
// }
inline double RandomDouble (double min, double max){
    // return real number betwenn [min,max]
    return min+(max-min)* RandomDouble();
}
// permet de clamper une valeur
inline double Clamp(double x, double min , double max){
    if (x<min) return min ;
    if (x> max) return max;
    return x;
}
//common headers

#include"Ray.h"
#include"Vec3.h"

#endif // !