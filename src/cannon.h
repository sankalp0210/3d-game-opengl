#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef CANNON_H
#define CANNON_H

class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z, float r,float h);
    glm::vec3 position, dir;
    glm::mat4 rotate;
    float radius = 0;
    int timer = 0;
    bool visible = true;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    void tick();
    bounding_box_t bounding_box();
private:
    std::vector<Cylinder> objects;
};

#endif // Cannon_H
