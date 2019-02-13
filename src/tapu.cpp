#include "main.h"
#include "tapu.h"
#include "cylinder.h"

Tapu::Tapu(float x, float y, float z, float r, color_t color) {
	this->color = color;
	this->set_position(x, y, z);
    int n = 50;
    this->radius = r;
    GLfloat vertex_buffer_data[] = {
         r, 0,  r,
        -r, 0,  r,
         r, 0, -r,

        -r, 0, -r,
        -r, 0,  r,
         r, 0, -r,
    };
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Tapu::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

bool Tapu::tick() {
}

void Tapu::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model = ( translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


bounding_box_t Tapu::bounding_box() {
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
