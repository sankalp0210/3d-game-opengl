#include "main.h"
#include "tapu.h"
#include "cylinder.h"

Tapu::Tapu(float x, float y, float z, float r, color_t color) {
	this->color = color;
	this->set_position(x, y, z);
    int n = 50;
    this->radius = r;
    GLfloat g_vertex_buffer_data[9*n+100];
	GLfloat deg = 2*3.1415926/((float)n);
    float x1 = r, z1 = 0.0f, y1 = 0.0f;
	for(int i=0;i<n;i++){
		GLfloat o = deg*(i+1);
		g_vertex_buffer_data[9*i + 0] = y1;
		g_vertex_buffer_data[9*i + 1] = y1;
		g_vertex_buffer_data[9*i + 2] = y1;
		g_vertex_buffer_data[9*i + 3] = x1;
		g_vertex_buffer_data[9*i + 4] = y1;
		g_vertex_buffer_data[9*i + 5] = z1;
		g_vertex_buffer_data[9*i + 6] = x1 = (r*cos(o));
		g_vertex_buffer_data[9*i + 7] = y1;
		g_vertex_buffer_data[9*i + 8] = z1 = (r*sin(o));
	}
    this->object=create3DObject(GL_TRIANGLES,n*3,g_vertex_buffer_data, COLOR_GREEN, GL_FILL);
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
