#include "main.h"

#ifndef CYLINDER_H
#define CYLINDER_H

class Cylinder {
public:
    Cylinder() {}
    Cylinder(int n, float x, float y, float z, float r11, float r12, float r21, float r22, float h, color_t color);
    glm::vec3 position, speed, rotation;
    color_t color;
    float radius = 0;
    bool visible = true;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    void set_speed(float x_speed, float y_speed, float z_speed);
    void set_rotation(float x_rot, float y_rot, float z_rot);
    bool tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Cylinder_H
