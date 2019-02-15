#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef FUEL_H
#define FUEL_H

class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    float val = 1.0f;
    void set_position(float x, float y ,float z);
    void tick();
private:
    VAO *object[2];
};

#endif // Fuel_H
