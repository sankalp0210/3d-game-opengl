#include "main.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H


class Triangle {
public:
    Triangle() {}
    Triangle(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
    };

#endif // Triangle_H
