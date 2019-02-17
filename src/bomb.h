#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef BOMB_H
#define BOMB_H

class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, float r,float h, glm::vec3 dir, glm::mat4 rotate, float speed);
    glm::vec3 position, rotation, dir;
    glm::mat4 rotate;
    float radius = 0, speed = 0;
    bool visible = true;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    void tick();
    bounding_box_t bounding_box();
private:
    std::vector<Cylinder> objects;
};

#endif // Bomb_H
