#include "main.h"
#include "alt.h"
#include "cylinder.h"

Alt::Alt(float x, float y, float maxval) {
	this->set_position(x, y, 0);
    float len = 3.0f, hgt = 12.0f, var = 0.25f;
    this->maxval = maxval/hgt;
    GLfloat vertex_buffer_data1[40] = {
          0,   var, 0,
          0, 2*var, 0,
        len, 2*var, 0,
          0,   var, 0,
        len,   var, 0,
        len, 2*var, 0,
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
    this->object[0] = create3DObject(GL_TRIANGLES, 8*3,vertex_buffer_data2, COLOR_BLACK, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3,vertex_buffer_data1, COLOR_RED, GL_FILL);

}

void Alt::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Alt::tick() {
}

void Alt::draw(glm::mat4 VP) {
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model = (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);

    this->position.y += (this->val+50.0f)/this->maxval;
    translate = glm::translate (this->position);    // glTranslatef
    Matrices.model = (translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[1]);
    this->position.y -= (this->val+50.0f)/this->maxval;
}
