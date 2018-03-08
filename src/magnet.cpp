#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    double ang = (double)M_PI / 180;


    static GLfloat vertex_buffer_data[] = {
      // first rectangle
      0,3.2,0,
      0,3,0,
      -1,3,0,

      0,3.2,0,
      -1,3,0,
      -1,3.2,0,

// second rectangle
      0,1,0,
      0,0.8,0,
      -1,0.8,0,

      0,1,0,
      -1,0.8,0,
      -1,1,0,

// third rectangle
      -2,2.5,0,
      -1.8,2.5,0,
      -1.8,1.5,0,

      -2,2.5,0,
      -2,1.5,0,
      -1.8,1.5,0,

// fourh rectangle
      -1,3.2,0,
      -1,3,0,
      -2,2.5,0,

      -2,2.5,0,
      -1.8,2.5,0,
      -1,3,0,

      // fifth rectangle

      -2,1.5,0,
      -1.8,1.5,0,
      -1,1,0,

      -1,1,0,
      -1,0.8,0,
      -2,1.5,0,


    };


    this->object = create3DObject(GL_TRIANGLES, 30, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::tick() {
  
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
