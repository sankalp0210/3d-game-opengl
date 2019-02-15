#include "main.h"
#include "cylinder.h"

Cylinder::Cylinder(int n, float x, float y, float z, float r11, float r12, float r21, float r22, float h, color_t color) {
	this->color = color;
	this->radius = radius;
	this->set_position(x, y, z);
    this->set_rotation(0, 0, 0);
	this->set_speed(0, 0, 0);

    GLfloat vertex_buffer_data[4*9*n+100];
	GLfloat deg = 2*3.1415926/((float)n), o = 0.0f, o1 = 0.0f;
    float x1 = r11, y1 = 0.0f, z1 = h/2, z2 = -h/2;
	for(int i=0;i<n;i++){
		o = deg*(i+1);
		vertex_buffer_data[9*i + 0] = 0;
		vertex_buffer_data[9*i + 1] = 0;
		vertex_buffer_data[9*i + 2] = z1;
		vertex_buffer_data[9*i + 3] = x1;
		vertex_buffer_data[9*i + 4] = y1;
		vertex_buffer_data[9*i + 5] = z1;
		vertex_buffer_data[9*i + 6] = x1 = (r11*cos(o));
		vertex_buffer_data[9*i + 7] = y1 = (r12*sin(o));
		vertex_buffer_data[9*i + 8] = z1;
	}
    x1 = r21; y1 = 0.0f;
    for(int i=n;i<2*n;i++){
		o = deg*(i+1);
		vertex_buffer_data[9*i + 0] = 0;
		vertex_buffer_data[9*i + 1] = 0;
		vertex_buffer_data[9*i + 2] = z2;
		vertex_buffer_data[9*i + 3] = x1;
		vertex_buffer_data[9*i + 4] = y1;
		vertex_buffer_data[9*i + 5] = z2;
		vertex_buffer_data[9*i + 6] = x1 = (r21*cos(o));
		vertex_buffer_data[9*i + 7] = y1 = (r22*sin(o));
		vertex_buffer_data[9*i + 8] = z2;
	}
    x1 = r11; y1 =0;
    for(int i=2*n;i<3*n;i++){
		o = deg*(i+1);
		o1 = deg*(i);
		vertex_buffer_data[9*i + 0] = (r21*cos(o1));
		vertex_buffer_data[9*i + 1] = (r22*sin(o1));
		vertex_buffer_data[9*i + 2] = z2;
		vertex_buffer_data[9*i + 3] = x1;
		vertex_buffer_data[9*i + 4] = y1;
		vertex_buffer_data[9*i + 5] = z1;
		vertex_buffer_data[9*i + 6] = x1 = (r11*cos(o));
		vertex_buffer_data[9*i + 7] = y1 = (r12*sin(o));
		vertex_buffer_data[9*i + 8] = z1;
	}
	x1 = r21*cos(deg*3*n); y1 = 0;
    for(int i=3*n;i<4*n;i++){
		o = deg*(i+1);
		o1 = deg*(i+1);
		vertex_buffer_data[9*i + 0] = (r11*cos(o1));
		vertex_buffer_data[9*i + 1] = (r12*sin(o1));
		vertex_buffer_data[9*i + 2] = z1;
		vertex_buffer_data[9*i + 3] = x1;
		vertex_buffer_data[9*i + 4] = y1;
		vertex_buffer_data[9*i + 5] = z2;
		vertex_buffer_data[9*i + 6] = x1 = (r21*cos(o));
		vertex_buffer_data[9*i + 7] = y1 = (r22*sin(o));
		vertex_buffer_data[9*i + 8] = z2;
	}
	
	this->object = create3DObject(GL_TRIANGLES, 3*n*4, vertex_buffer_data, color, GL_FILL);
}

void Cylinder::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Cylinder::set_rotation(float x_rot, float y_rot, float z_rot) {
    this->rotation = glm::vec3(x_rot, y_rot, z_rot);
}

void Cylinder::set_speed(float x_speed, float y_speed, float z_speed) {
	this->speed = glm::vec3(x_speed, y_speed, z_speed);
}


bool Cylinder::tick() {
}


void Cylinder::draw(glm::mat4 VP) {
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


bounding_box_t Cylinder::bounding_box() {
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
