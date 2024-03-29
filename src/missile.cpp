#include "main.h"
#include "missile.h"
#include "cylinder.h"

Missile::Missile(float x, float y, float z, float r, float h, glm::vec3 dir, glm::mat4 rotate) {
    this->dir = dir;
    this->rotate = rotate;
	this->set_position(x, y, z);
    objects.push_back(Cylinder(50, 0, 0, 0, r, r, r, r, 3*h/4, COLOR_MISSILE));
    objects.push_back(Cylinder(50, 0, 0, -h/2, r, r, 0, 0, h/4, COLOR_MISSILE));
    this->radius = h;
}

void Missile::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Missile::tick() {
    float sp = 2.0f;
    this->position.x -= sp*dir[0];
    this->position.y -= sp*dir[1];
    this->position.z -= sp*dir[2];
}
void Missile::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(auto ob:objects)
        ob.draw(MVP);
}

bounding_box_t Missile::bounding_box() {
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
