#ifndef COLOR_H
#define COLOR_H

#include"Vec3.h"

#include<iostream>
// Color N'est pa sune calsse c'est un derive de Vec3

void WriteColor(std::ostream &out, Color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale*r);
    g = sqrt(scale*g);
    b = sqrt(scale*b);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * Clamp(r,0.0,0.999)) <<' '
        << static_cast<int>(256 * Clamp(g,0.0,0.999)) <<' '
        << static_cast<int>(256 * Clamp(b,0.0,0.999)) <<'\n';
}






//ancienne methode


#endif 