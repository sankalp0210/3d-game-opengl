#include "main.h"
#include "cylinder.h"
#include <vector>

#ifndef ALT_H
#define ALT_H

class Alt {
public:
    Alt() {}
    Alt(float x, float y, float maxval);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    float val = 0, maxval = 0;
    void set_position(float x, float y ,float z);
    void tick();
private:
    VAO *object[2];
};

#endif // Alt_H
