#include "water.h"
#include "main.h"

Water::Water(float radius, float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radius;

    double ang = (double)M_PI / 180;

    static GLfloat vertex_buffer_data[180*9];

    for(int i=0;i<180;i++)
    {
      vertex_buffer_data[i*9] = 0.0f;
      vertex_buffer_data[i*9+1] = 0.0f;
      vertex_buffer_data[i*9+2] = 0.0f;
      vertex_buffer_data[i*9+3] = radius * (float)cos(i * 1 * ang);
      vertex_buffer_data[i*9+4] = -radius * (float)sin(i * 1 * ang);
      vertex_buffer_data[i*9+5] = 0.0f;
      vertex_buffer_data[i*9+6] = radius * (float)cos((i+1) * 1 * ang);
      vertex_buffer_data[i*9+7] = -radius * (float)sin((i+1) * 1  * ang);
      vertex_buffer_data[i*9+8] = 0.0f;
    }


    this->object = create3DObject(GL_TRIANGLES, 180*3, vertex_buffer_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Water::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
