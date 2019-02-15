#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef HEALTH_H
#define HEALTH_H

class Health {
public:
    Health() {}
    Health(float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    float val = 1.0f;
    void set_position(float x, float y ,float z);
    void tick();
private:
    VAO *object[2];
};

#endif // Health_H
