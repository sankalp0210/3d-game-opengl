#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef MOUNT_H
#define MOUNT_H

class Mount {
public:
    Mount() {}
    Mount(float x, float y, float z, float r,float h);
    glm::vec3 position, rotation;
    float radius = 0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    bool tick();
    bounding_box_t bounding_box();
private:
    std::vector<Cylinder> objects;
};

#endif // Mount_H
