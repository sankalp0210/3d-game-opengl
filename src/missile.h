#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, float r,float h);
    glm::vec3 position, rotation;
    float radius = 0;
    bool visible = true;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    bool tick();
    bounding_box_t bounding_box();
private:
    std::vector<Cylinder> objects;
};

#endif // Missile_H
