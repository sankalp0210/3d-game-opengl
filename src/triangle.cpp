#include "triangle.h"
#include "main.h"

Triangle::Triangle(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    float var = 1.0f;
    GLfloat vertex_buffer_data[20] = {
         -var,  0.5f, 0, 
          var, -0.25f, 0,
         -var, -0.25f, 0, 
         -var,  0.5f, 0, 
          var, -0.25f, 0,
          var,  0.5f, 0,
    };
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Triangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Triangle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Triangle::tick() {
    if(this->position.x < (screen_center_x - 16))
        this->position.x += 40;
    if(this->position.x > (screen_center_x + 16))
        this->position.x -= 40;
}
