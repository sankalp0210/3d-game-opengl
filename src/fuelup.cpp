#include "main.h"
#include "fuelup.h"
#include "cylinder.h"

Fuelup::Fuelup(float x, float y, float z, float r, float h) {
	this->set_position(x, y, z);
    objects.push_back(Cylinder(50, 0, 0, 0, r, r, r, r, h, {200, 0, 0}));
    this->radius = h;
}

void Fuelup::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Fuelup::tick() {
}
void Fuelup::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model = (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(auto ob:objects)
        ob.draw(MVP);
}

bounding_box_t Fuelup::bounding_box() {
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
