#include "porcupine.h"
#include "main.h"

Porcupine::Porcupine(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    static GLfloat vertex_buffer_data[] = {
      -1.5,-1.2,0,
      -1.7,-0.8,0,
      -1.9,-1.2,0,

      -1.9,-1.2,0,
      -2.1,-0.8,0,
      -2.3,-1.2,0,

      -2.3,-1.2,0,
      -2.5,-0.8,0,
      -2.7,-1.2,0,

    };


    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, color, GL_FILL);
}

void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porcupine::tick() {
    this->position.x += speed;
    if(this->position.x >= 1.3 || this->position.x <= -5){
      speed = -1 * speed;
    }
}

void Porcupine::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


bounding_box_t Porcupine::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float height = 0.7;
    bounding_box_t bbox = { x, y, height};
    return bbox;
}
