#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef SEA_H
#define SEA_H

class Sea {
public:
    Sea() {}
    Sea(float x, float y, float z, float r, color_t color);
    glm::vec3 position;
    color_t color;
    float radius = 0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    bool tick();
private:
    VAO *object;
};

#endif // Sea_H
