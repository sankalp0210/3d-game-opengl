#include "main.h"

#ifndef SMOKE_H
#define SMOKE_H

class Smoke {
public:
    Smoke() {}
    Smoke(int n, float x, float y, float z, float r1, float r2, float h);
    glm::vec3 position, rotation;
    float radius = 0;
    bool visible = true;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    void set_rotation(float x_rot, float y_rot, float z_rot);
    bool tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Smoke_H
