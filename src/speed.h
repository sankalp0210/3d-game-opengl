#include "main.h"

#ifndef SPEED_H
#define SPEED_H


class Speed {
public:
    Speed() {}
    Speed(float x, float y);
    glm::vec3 position;
    float rot;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object[3];
};

#endif // Speed_H
