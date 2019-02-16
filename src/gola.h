#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef GOLA_H
#define GOLA_H

class Gola {
public:
    Gola() {}
    Gola(float x, float y, float z, float r,float h, glm::vec3 dir, glm::mat4 rotate);
    glm::vec3 position, rotation, dir;
    glm::mat4 rotate;
    float radius = 0;
    bool visible = true;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    void tick();
    bounding_box_t bounding_box();
private:
    std::vector<Cylinder> objects;
};

#endif // Gola_H
