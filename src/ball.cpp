#include "ball.h"
#include "main.h"

Ball::Ball(int flag_player, float radius, float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = ((double)rand()/RAND_MAX) * 0.01;
    speedY = 0.3;
    acc = 0.05;
    this->radius = radius;

    double ang = (double)M_PI / 180;

    static GLfloat vertex_buffer_data[360*9];

    for(int i=0;i<360;i++)
    {
      vertex_buffer_data[i*9] = 0.0f;
      vertex_buffer_data[i*9+1] = 0.0f;
      vertex_buffer_data[i*9+2] = 0.0f;
      vertex_buffer_data[i*9+3] = radius * (float)cos(i * 1 * ang);
      vertex_buffer_data[i*9+4] = radius * (float)sin(i * 1 * ang);
      vertex_buffer_data[i*9+5] = 0.0f;
      vertex_buffer_data[i*9+6] = radius * (float)cos((i+1) * 1 * ang);
      vertex_buffer_data[i*9+7] = radius * (float)sin((i+1) * 1  * ang);
      vertex_buffer_data[i*9+8] = 0.0f;
    }


    this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x += speed;

    if(flag_player==1) {
      this->position.y += this->speedY;

      // magnet condition
      // if(this->position.y <= 3.2 && this->position.y >= 0.8){
        // this->position.x -= 0.05;
        // this->position.y += 0.01;
      // }

      // pond condition
      if(this->position.y <= -1 && this->position.x > 0.2 && this->position.x < 1.2){
        this->position.y = -1.45 - sqrt(0.25-((this->position.x - 0.7)*(this->position.x - 0.7)));
        // this->speedY = 0.7;
      }

      // pond condition
      else if(this->position.y <= -1 && this->position.x >= -0.3 && this->position.x <= 0.2){
        this->position.y = (-1 * this->position.x) - 1.3;
        // this->speedY = 0.7;
      }

      // pond condition
      else if(this->position.y <= -1 && this->position.x >= 1.2 && this->position.x <= 1.7){
        this->position.y = (this->position.x) - 2.7;
      }


      else if(this->position.y > -1){
          this->speedY -= this->acc;
      }


      else if(this->position.y < -1){
        this->speedY = 0;
        this->set_position(this->position.x , -1);
      }
    }
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
