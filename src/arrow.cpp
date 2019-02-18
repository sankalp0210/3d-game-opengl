#include "main.h"
#include "arrow.h"
#include "cylinder.h"

Arrow::Arrow(float x, float y, float z, float r, float h) {
    this->rotate = glm::mat4(1.0f);
	this->set_position(x, y, z);
    objects.push_back(Cylinder(50, 0, 0,     0, r, r/4, r, r/4, 3*h/4, {200, 0, 0}));
    objects.push_back(Cylinder(50, 0, 0, -h/2, 3*r/2, r/4, 0, 0, h/4, {250, 0, 0}));
}

void Arrow::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Arrow::tick() {
}

void Arrow::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::vec3 th = glm::cross(this->dir, glm::vec3(this->dir[1], -this->dir[0], 0));
    this->rotate[2][0] = this->dir[0];this->rotate[2][1] = this->dir[1];this->rotate[2][2] = this->dir[2];
    this->rotate[1][0] = this->dir[1];this->rotate[1][1] = -this->dir[0];this->rotate[1][2] = 0;
    this->rotate[0][0] = th[0];this->rotate[0][1] = th[1];this->rotate[0][2] =th[2];

    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(auto ob:objects)
        ob.draw(MVP);
}
