#include "main.h"
#include "smoke.h"

Smoke::Smoke(int n, float x, float y, float z, float r1, float r2, float h) {
	this->radius = r1 / 3;
	this->set_position(x, y, z);
    this->set_rotation(0, 0, 0);
    GLfloat vertex_buffer_data[2*9*n+100];
	GLfloat deg = 2*3.1415926/((float)n), o = 0.0f, o1 = 0.0f;
    float x1 = r1, y1 = 0.0f, z1 = h/2, z2 = -h/2;
    x1 = r1; y1 =0;
    for(int i=0;i<n;i++){
		o = deg*(i+1);
		o1 = deg*(i);
		vertex_buffer_data[9*i + 0] = (r2*cos(o1));
		vertex_buffer_data[9*i + 1] = (r2*sin(o1));
		vertex_buffer_data[9*i + 2] = z2;
		vertex_buffer_data[9*i + 3] = x1;
		vertex_buffer_data[9*i + 4] = y1;
		vertex_buffer_data[9*i + 5] = z1;
		vertex_buffer_data[9*i + 6] = x1 = (r1*cos(o));
		vertex_buffer_data[9*i + 7] = y1 = (r1*sin(o));
		vertex_buffer_data[9*i + 8] = z1;
	}
	x1 = r2*cos(deg*3*n); y1 = 0;
    for(int i=n;i<2*n;i++){
		o = deg*(i+1);
		o1 = deg*(i+1);
		vertex_buffer_data[9*i + 0] = (r1*cos(o1));
		vertex_buffer_data[9*i + 1] = (r1*sin(o1));
		vertex_buffer_data[9*i + 2] = z1;
		vertex_buffer_data[9*i + 3] = x1;
		vertex_buffer_data[9*i + 4] = y1;
		vertex_buffer_data[9*i + 5] = z2;
		vertex_buffer_data[9*i + 6] = x1 = (r2*cos(o));
		vertex_buffer_data[9*i + 7] = y1 = (r2*sin(o));
		vertex_buffer_data[9*i + 8] = z2;
	}
	this->rotation.x = 90.0f;
	this->object = create3DObject(GL_TRIANGLES, 3*n*2, vertex_buffer_data,{95, 158, 160}, GL_FILL);
}

void Smoke::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Smoke::set_rotation(float x_rot, float y_rot, float z_rot) {
    this->rotation = glm::vec3(x_rot, y_rot, z_rot);
}


bool Smoke::tick() {
	if(this->timer)
		this->timer++;
	if(this->timer > 120)
		this->timer = 0;
}


void Smoke::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_x  = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y  = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z  = glm::rotate((float) (this->rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate );
    // Matrices.model *= (translate * rotate_y * rotate_z * rotate_x);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


bounding_box_t Smoke::bounding_box() {
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
