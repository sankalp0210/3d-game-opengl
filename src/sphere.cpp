#include "main.h"
#include "sphere.h"
 
Sphere::Sphere(float x, float y, float z, float radius, color_t color) {
	this->color = color;
	this->radius = radius;
	this->set_position(x, y, z);
    this->set_rotation(0, 0, 0);
	this->set_speed(0, 0, 0);

    int n = 100;
	GLfloat vertex_buffer_data[10 * n * (1 + n)];
    float k = (2 * M_PI) / n;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            int idx = 9 * (n * j + i);
            vertex_buffer_data[idx] = 0.0f,
            vertex_buffer_data[idx + 1] = 0.0f,
            vertex_buffer_data[idx + 2] = this->radius * sin(i * k),
            vertex_buffer_data[idx + 3] = this->radius * cos(j * k) * cos(i * k),
            vertex_buffer_data[idx + 4] = this->radius * sin(j * k) * cos(i * k),
            vertex_buffer_data[idx + 5] = this->radius * sin(i * k),
            vertex_buffer_data[idx + 6] = this->radius * cos((j + 1) * k) * cos(i * k),
            vertex_buffer_data[idx + 7] = this->radius * sin((j + 1 ) * k) * cos(i * k),
            vertex_buffer_data[idx + 8] = this->radius * sin(i * k);
        }

    this->object = create3DObject(GL_TRIANGLES, 3 * n * n, vertex_buffer_data, color, GL_FILL);
}

void Sphere::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Sphere::set_rotation(float x_rot, float y_rot, float z_rot) {
    this->rotation = glm::vec3(x_rot, y_rot, z_rot);
}

void Sphere::set_speed(float x_speed, float y_speed, float z_speed) {
	this->speed = glm::vec3(x_speed, y_speed, z_speed);
}


bool Sphere::tick() {
    this->rotation.x += 1.0f;
    this->position.y += this->speed.y;
    this->position.z -= this->speed.z * cos(this->rotation.y * M_PI / 180.0f);
    this->position.x += this->speed.x * sin(this->rotation.y * M_PI / 180.0f);
}


void Sphere::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_y  = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z  = glm::rotate((float) (this->rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate_x  = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate_y * rotate_z * rotate_x);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


bounding_box_t Sphere::bounding_box() {
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
