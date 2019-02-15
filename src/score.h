#include "main.h"

#ifndef SCORE_H
#define SCORE_H


class Score {
public:
    Score() {}
    Score(float x, float y);
    glm::vec3 position;
    float rotation;
    std::string str[10];
    void draw(glm::mat4 VP, int num, int dis);
    void set_position(float x, float y);
    void tick(int i);
private:
    VAO *object[8];
};

#endif // Score_H
