#include "main.h"
#include "plane.h"
#include "cylinder.h"

Plane::Plane(float x, float y, float z, color_t color) {
	this->color = color;
	this->radius = radius;
	this->set_position(x, y, z);
    this->set_rotation(0, 0, 0);
	this->set_speed(0.1f, 0.1f, 0.1f);
	this->ret = glm::mat4(1.0f);
	float rBodyT = 1.0f, rBodyB = 1.0f, hBody = 5.0f;
	float rTop = 0.1f, hTop = 3.0f;
	float rBot = 1.5f, hBot = 2.0f;
	parts.push_back(Cylinder( 50, x, y, z, rBodyT, rBodyT, rBodyB, rBodyB, hBody, color));
	parts.push_back(Cylinder( 50, x, y,z-(hBody+hTop)/2, rBodyT, rBodyT, rTop, rTop, hTop, color));
	// parts.push_back(Cylinder(50,x,y,z-(hBody+hBot)/2,rBody,rBody,rBot,rBot,hBot,color));
    float var1 = x + rBot/2;
    float var2 = x - rBot/2;
	float wing = 3.0f;
	GLfloat vertex_buffer_data1[20] = {
        var1     , 0,   z, 
        var1     , 0, z+2,
        var1+wing, 0, z+2,

        var2     , 0,   z, 
    	var2     , 0, z+2,
    	var2-wing, 0, z+2,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
    // this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, color, GL_FILL);
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
}


void Plane::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_x  = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y  = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z  = glm::rotate((float) (this->rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));
	ret *= rotate_z * rotate_y *rotate_x;
    Matrices.model *= ( translate * ret);
	
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object2);
    draw3DObject(this->object1);
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
