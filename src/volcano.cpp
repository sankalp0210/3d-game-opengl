#include "main.h"
#include "volcano.h"
#include "cylinder.h"

Volcano::Volcano(float x, float y, float z, float r, float h) {
	this->set_position(x, y, z);
    objects.push_back(Cylinder(50, 0, 0, 0, r, r, r/2, r/2, h/2, COLOR_VOLCANO_DOWN));
    objects.push_back(Cylinder(50, 0, 0, -h/2, r/2, r/2, r/4, r/4, h/2, COLOR_VOLCANO_UP));
    this->rotation.x = 90.0f;
}

void Volcano::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

bool Volcano::tick() {
}

void Volcano::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_x  = glm::rotate((float)(this->rotation.x*M_PI /180.0f), glm::vec3(1, 0, 0));
    Matrices.model = (translate * rotate_x);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(auto ob:objects)
        ob.draw(MVP);
}

bounding_box_t Volcano::bounding_box() {
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
