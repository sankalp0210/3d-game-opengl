#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef PLANE_H
#define PLANE_H

class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z, color_t color);
    glm::vec3 position, speed, rotation;
    std::vector<Cylinder> parts;
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

#endif // Plane_H
