#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef PARA_H
#define PARA_H

class Para {
public:
    Para() {}
    Para(float x, float y, float z, float r);
    glm::vec3 position;
    float radius = 0, angle = 0;
    bool visible = true;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    void tick();
    bounding_box_t bounding_box();
private:
    std::vector<Cylinder> objects;
    VAO *obj;
};

#endif // Para_H
