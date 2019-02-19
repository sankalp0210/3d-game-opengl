#include "main.h"
#include "para.h"
#include "cylinder.h"

Para::Para(float x, float y, float z, float r) {
	this->set_position(x, y, z);
    GLfloat deg = (2*3.1415926/360.0f);    
    for(int i=2;i<=90;i+=2)
    {   
        float o1 = deg*(i-2);
        float o2 = deg*i;
        float r1 = r*cos(o1);
        float r2 = r*cos(o2);
        float h = r*sin(o2);
        float h1 = r*sin(o2) - r*sin(o1);
        objects.push_back(Cylinder(50, 0, 0, -h, r1, r1, r2, r2, h1, {205, 92, 92}));
    }
    objects.push_back(Cylinder(50, 0, 0, r, r/4, r/4, r/4, r/4, r/4, {0, 0, 0}));
    GLfloat vertex_buffer_data[40] = {
         r,  0,  0,
         r-0.5f,  0,  0,
         0,  0,  r,

        -r,  0, 0,
        -r+0.5f,  0, 0,
         0,  0, r,
    };
    this->obj = create3DObject(GL_TRIANGLES, 2*3,vertex_buffer_data, {0, 0, 0}, GL_FILL);
    this->radius = 2*r;
    this->angle = 90.0f;
}

void Para::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Para::tick() {
    this->position.y -= this->speed;
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
