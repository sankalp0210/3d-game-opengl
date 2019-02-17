#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y);
    glm::vec3 position;
    glm::mat4 rotate;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(glm::vec3 dir);
private:
    VAO *object[3];
};

#endif // Compass_H
