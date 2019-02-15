#include "main.h"
#include "health.h"
#include "cylinder.h"

Health::Health(float x, float y) {
	this->set_position(x, y, 0);
    float len = 6.0f, hgt = 3.0f, var = 0.25f;
    GLfloat vertex_buffer_data1[40] = {
          0,   0, 0,
          0, hgt, 0,
        len, hgt, 0,
          0,   0, 0,
        len,   0, 0,
        len, hgt, 0,
    };
    GLfloat vertex_buffer_data2[80] = {
         len+var,  hgt+var, 0,
         len+var,  hgt-var, 0,
            -var,  hgt+var, 0,
         len+var,  hgt-var, 0,
            -var,  hgt-var, 0,
            -var,  hgt+var, 0,

         len+var, +var, 0,
         len+var, -var, 0,
            -var, +var, 0,
         len+var, -var, 0,
            -var, -var, 0,
            -var, +var, 0,

         len+var, hgt+var, 0,
         len+var, -var, 0,
         len-var, hgt+var, 0,
         len+var, -var, 0,
         len-var, -var, 0,
         len-var, hgt+var, 0,

        +var,  hgt+var, 0,
        +var, -var, 0,
        -var,  hgt+var, 0,
        +var, -var, 0,
        -var, -var, 0,
        -var,  hgt+var, 0,
    };
    this->object[0] = create3DObject(GL_TRIANGLES, 8*3,vertex_buffer_data2, COLOR_HEALTH_B, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3,vertex_buffer_data1, COLOR_HEALTH, GL_FILL);

}

void Health::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Health::tick() {
}

void Health::draw(glm::mat4 VP) {
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model = (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    
    translate[0][0] = this->val;
    Matrices.model = (translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[1]);
}
