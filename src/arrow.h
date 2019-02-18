#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef ARROW_H
#define ARROW_H

class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z, float r,float h);
    glm::vec3 position, dir;
    glm::mat4 rotate;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    void tick();
private:
    std::vector<Cylinder> objects;
};

#endif // Arrow_H
