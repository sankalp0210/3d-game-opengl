#include "main.h"
#include "missile.h"
#include "cylinder.h"

Missile::Missile(float x, float y, float z, float r, float h) {
	this->set_position(x, y, z);
    objects.push_back(Cylinder(50, 0, 0, 0, r, r, r, r, 3*h/4, COLOR_BLACK));
    objects.push_back(Cylinder(50, 0, 0, -h/2, r, r, 0, 0, h/4, COLOR_BLACK));
    this->rotation.x = 90.0f;
}

void Missile::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Missile::tick() {
    this->position.z -= 0.5f;
}

void Missile::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_x  = glm::rotate((float)(this->rotation.x*M_PI /180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y  = glm::rotate((float)(this->rotation.y*M_PI /180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z  = glm::rotate((float)(this->rotation.z*M_PI /180.0f), glm::vec3(0, 0, 1));

    Matrices.model = (translate * rotate_y * rotate_x * rotate_z);
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
