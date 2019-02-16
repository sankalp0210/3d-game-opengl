#include "main.h"
#include "para.h"
#include "cylinder.h"

Para::Para(float x, float y, float z, float r) {
	this->set_position(x, y, z);
    objects.push_back(Cylinder(50, 0, 0, 0, r, r, 0, 0, r, COLOR_GREEN));
    GLfloat vertex_buffer_data[40] = {
         0,  r,  0,
         0,  0, -r,
         0, -r,  0,
         0,  0, -r,
         r,  0,  0,
         0,  0, -r,
        -r,  0,  0,
         0,  0, -r,
    };
    this->obj = create3DObject(GL_LINE, 4*2,vertex_buffer_data, COLOR_GREEN, GL_FILL);

    this->angle = 90.0f;
}

void Para::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Para::tick() {
    // this->position.x -= 0.5f*dir[0];
    // this->position.y -= 0.5f*dir[1];
    // this->position.z -= 0.5f*dir[2];
}
void Para::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->angle * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model = (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->obj);
    for(auto ob:objects)
        ob.draw(MVP);
}

bounding_box_t Para::bounding_box() {
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
