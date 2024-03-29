#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, float r,float h, glm::vec3 dir, glm::mat4 rotate);
    glm::vec3 position, rotation, dir;
    glm::mat4 rotate;
    float radius = 0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    void tick();
    bounding_box_t bounding_box();
private:
    std::vector<Cylinder> objects;
};

#endif // Missile_H
