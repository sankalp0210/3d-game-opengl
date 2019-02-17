#include "compass.h"
#include "main.h"

Compass::Compass(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    int n = 50;
    GLfloat g_vertex_buffer_data[9*n+100];
	GLfloat deg = 2*3.1415926/((float)n), r = 3.0f;
    float x1 = r, y1 = 0.0f, z = 0.0f;
	for(int i=0;i<n;i++){
		GLfloat o = deg*(i+1);
		g_vertex_buffer_data[9*i + 0] = z;
		g_vertex_buffer_data[9*i + 1] = z;
		g_vertex_buffer_data[9*i + 2] = z;
		g_vertex_buffer_data[9*i + 3] = x1;
		g_vertex_buffer_data[9*i + 4] = y1;
		g_vertex_buffer_data[9*i + 5] = z;
		g_vertex_buffer_data[9*i + 6] = x1 = (r*cos(o));
		g_vertex_buffer_data[9*i + 7] = y1 = (r*sin(o));
		g_vertex_buffer_data[9*i + 8] = z;
	}
    this->object[0]=create3DObject(GL_TRIANGLES,n*3,g_vertex_buffer_data, {245,222,179}, GL_FILL);
    
    float hgt = r, var = 0.5f;
    GLfloat vertex_buffer_data1[10] = {
         var,   0, 0,
           0, hgt, 0,
        -var,   0, 0,
    };
    this->object[1]=create3DObject(GL_TRIANGLES,3,vertex_buffer_data1,COLOR_FUEL,GL_FILL);
    GLfloat vertex_buffer_data2[10] = {
         var,   0, 0,
           0, -hgt, 0,
        -var,   0, 0,
    };
    this->object[2]=create3DObject(GL_TRIANGLES,3, vertex_buffer_data2,COLOR_SEA,GL_FILL);    
}

void Compass::draw(glm::mat4 VP) {
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
}

void Compass::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Compass::tick(glm::vec3 dir) {
    this->rotate = glm::rotate((float) ((atan2((double)dir.z, (double)dir.x)) - (M_PI / 2.0f)), glm::vec3(0, 0, 1));
}
