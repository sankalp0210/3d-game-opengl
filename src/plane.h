#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef PLANE_H
#define PLANE_H

class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z, color_t color);
    glm::vec3 position, rotation, dir, up, cr;
    std::vector<Cylinder> parts;
    color_t color;
    float radius = 0;
    bool visible = true;
    int timer = 0, missileTime = 0, sp = 0, score = 1, altitude = 0;
    float health = 1, fuel = 1, maxAlt = 50.0f, minAlt = -47.0f, acc = 0.01f, maxSpeed = 2.0f, drag = 0.005f, speed = 0;
    void draw(glm::mat4 VP);
    glm::mat4 ret;
    void set_position(float x, float y ,float z);
    void set_rotation(float x_rot, float y_rot, float z_rot);
    bool tick();
    bounding_box_t bounding_box();
private:
    VAO *object1;
    VAO *object2;
};
 
#endif // Plane_H
