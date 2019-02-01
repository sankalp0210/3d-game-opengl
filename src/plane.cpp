#include "main.h"
#include "plane.h"
#include "cylinder.h"

Plane::Plane(float x, float y, float z, color_t color) {
	this->color = color;
	this->radius = radius;
	this->set_position(x, y, z);
    this->set_rotation(0, 0, 0);
	this->set_speed(0, 0, 0);
	parts.push_back(Cylinder( 50, x, y, z, 2, 2, 2, 2, 5, color));
	parts.push_back(Cylinder( 50, x, y, z+4, 0.2, 0.2, 2, 2, 3, color));
	// parts.push_back(Cylinder( 50, x, y-2, z, 0.2, 0.2, 2, 2, 2, color));
	// parts[2].rotation.x = 90.0f;
}

void Plane::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Plane::set_rotation(float x_rot, float y_rot, float z_rot) {
    this->rotation = glm::vec3(x_rot, y_rot, z_rot);
}

void Plane::set_speed(float x_speed, float y_speed, float z_speed) {
	this->speed = glm::vec3(x_speed, y_speed, z_speed);
}


bool Plane::tick() {
    this->rotation.x += 1.0f;
    this->position.y += this->speed.y;
    this->position.z -= this->speed.z * cos(this->rotation.y * M_PI / 180.0f);
    this->position.x += this->speed.x * sin(this->rotation.y * M_PI / 180.0f);
}


void Plane::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_y  = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z  = glm::rotate((float) (this->rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate_x  = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate_y * rotate_z * rotate_x);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	for(auto prt:this->parts)
		prt.draw(MVP);
}


bounding_box_t Plane::bounding_box() {
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