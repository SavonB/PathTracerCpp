
#pragma once


#include "vec3.h"
#include <iostream>

void write_color(std::ostream& out, color pixel_color, int samplespp) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();
    
    //divide color by number of samples
    auto scale = 1.0 / samplespp;

    //gamma correction for 2.0
    r = sqrt(r*scale);
    g = sqrt(g*scale);
    b = sqrt(b*scale);


    //translate color to 255 range
    out << static_cast<int>(256 * clamp(r,0., .999)) <<' '
        << static_cast<int>(256 * clamp(g, 0., .999)) << ' '
        << static_cast<int>(256 * clamp(b, 0., .999)) <<'\n';
}

