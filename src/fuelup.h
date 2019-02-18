#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef FUELUP_H
#define FUELUP_H

class Fuelup {
public:
    Fuelup() {}
    Fuelup(float x, float y, float z, float r,float h);
    glm::vec3 position;
    float radius = 0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    void tick();
    bounding_box_t bounding_box();
private:
    std::vector<Cylinder> objects;
};

#endif // Fuelup_H
