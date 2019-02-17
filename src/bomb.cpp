#include "main.h"
#include "bomb.h"
#include "cylinder.h"

Bomb::Bomb(float x, float y, float z, float r, float h, glm::vec3 dir, glm::mat4 rotate, float speed) {
    this->dir = dir;
    this->rotate = rotate;
	this->set_position(x, y, z);
    objects.push_back(Cylinder(50, 0, 0, 0, r, r, r, r, 3*h/4, {0, 100, 0}));
    objects.push_back(Cylinder(50, 0, 0, -h/2, r, r, 0, 0, h/4, {0, 100, 0}));
}

void Bomb::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Bomb::tick() {
    this->position.x -= this->speed*dir[0];
    this->position.y -= 0.3f;
    this->position.z -= this->speed*dir[2];
}
void Bomb::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(auto ob:objects)
        ob.draw(MVP);
}

bounding_box_t Bomb::bounding_box() {
    bounding_box_t bbox = {
    	this->position.x,
    	this->position.y,
    	this->position.z,
    	this->radius,
    	this->radius,
    	this->radius
    };
    return bbox;
}
