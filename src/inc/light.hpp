#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "vec3.hpp"

class Light {
public:
    vec3 pos;
    
    Light(const vec3& pos);
};

#endif // LIGHT_HPP
