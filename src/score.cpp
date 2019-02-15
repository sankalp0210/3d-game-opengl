#include "score.h"
#include "main.h"

Score::Score(float x, float y) {
    color_t color = COLOR_SCORE;
    this->position = glm::vec3(x, y, 0);
    float len = 1.0f;
    float hgt = 2.0f;
    float var = 0.25f;
    GLfloat vertex_buffer_data1[40] = {
         len+var, hgt+var, 0,
         len+var, hgt-var, 0,
        -len-var, hgt+var, 0,
         len+var, hgt-var, 0,
        -len-var, hgt-var, 0,
        -len-var, hgt+var, 0,
    };
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color, GL_FILL);

    GLfloat vertex_buffer_data4[40] = {
         len+var, -hgt+var, 0,
         len+var, -hgt-var, 0,
        -len-var, -hgt+var, 0,
         len+var, -hgt-var, 0,
        -len-var, -hgt-var, 0,
        -len-var, -hgt+var, 0,
    };
    this->object[4] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, color, GL_FILL);

    GLfloat vertex_buffer_data7[40] = {
         len+var,  var, 0,
         len+var, -var, 0,
        -len-var,  var, 0,
         len+var, -var, 0,
        -len-var, -var, 0,
        -len-var,  var, 0,
    };
    this->object[7] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data7, color, GL_FILL);

    GLfloat vertex_buffer_data2[40] = {
         len+var, hgt+var, 0,
         len+var,    -var, 0,
         len-var, hgt+var, 0,
         len+var,    -var, 0,
         len-var,    -var, 0,
         len-var, hgt+var, 0,
    };
    this->object[2] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, color, GL_FILL);

    GLfloat vertex_buffer_data3[40] = {
         len+var, -hgt-var, 0,
         len+var,     -var, 0,
         len-var, -hgt-var, 0,
         len+var,     -var, 0,
         len-var,     -var, 0,
         len-var, -hgt-var, 0,
    };
    this->object[3] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, color, GL_FILL);

   GLfloat vertex_buffer_data5[40] = {
         -len+var, -hgt-var, 0,
         -len+var,     -var, 0,
         -len-var, -hgt-var, 0,
         -len+var,     -var, 0,
         -len-var,     -var, 0,
         -len-var, -hgt-var, 0,
    };
    this->object[5] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data5, color, GL_FILL);

   GLfloat vertex_buffer_data6[40] = {
         -len+var, hgt+var, 0,
         -len+var,    -var, 0,
         -len-var, hgt+var, 0,
         -len+var,    -var, 0,
         -len-var,    -var, 0,
         -len-var, hgt+var, 0,
    };
    this->object[6] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data6, color, GL_FILL);

   this->str[0] = "1111110";
   this->str[1] = "0110000";
   this->str[2] = "1101101";
   this->str[3] = "1111001";
   this->str[4] = "0110011";
   this->str[5] = "1011011";
   this->str[6] = "1011111";
   this->str[7] = "1110000";
   this->str[8] = "1111111";
   this->str[9] = "1110011";
}

void Score::draw(glm::mat4 VP, int num, int dis) {
    Matrices.model = glm::mat4(0.5f);
    this->position.x -= dis;
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<this->str[num].size();i++)
    {
        if(this->str[num][i] == '1')
            draw3DObject(this->object[i+1]);
    }
    this->position.x += dis;
}

void Score::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Score::tick(int i) {
}
