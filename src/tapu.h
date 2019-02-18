#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef TAPU_H
#define TAPU_H

class Tapu {
public:
    Tapu() {}
    Tapu(float x, float y, float z, float r, color_t color);
    glm::vec3 position;
    color_t color;
    float radius = 0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    bool tick();
private:
    VAO *object;
};

#endif // Tapu_H
