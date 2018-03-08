#include "trampoline.h"
#include "main.h"

Trampoline::Trampoline(float radius, float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radius;

    double ang = (double)M_PI / 180;

    static GLfloat vertex_buffer_data[(6*3)+(180*9)+(6*3)];


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

    vertex_buffer_data[1620] = -0.5;
    vertex_buffer_data[1621] = 0;
    vertex_buffer_data[1622] = 0;
    vertex_buffer_data[1623] = -0.6;
    vertex_buffer_data[1624] = 0;
    vertex_buffer_data[1625] = 0;
    vertex_buffer_data[1626] = -0.5;
    vertex_buffer_data[1627] = -1;
    vertex_buffer_data[1628] = 0;
    vertex_buffer_data[1629] = -0.6;
    vertex_buffer_data[1630] = 0;
    vertex_buffer_data[1631] = 0;
    vertex_buffer_data[1632] = -0.6;
    vertex_buffer_data[1633] = -1;
    vertex_buffer_data[1634] = 0;
    vertex_buffer_data[1635] = -0.5;
    vertex_buffer_data[1636] = -1;
    vertex_buffer_data[1637] = 0;


  //   -0.5,0,0,
  //   -0.7,0,0,
  //   -0.5,-1,0,
  //   -0.7,0,0,
  //   -0.5,-1,0,
  //   -0.5,-1,0,
  //


  vertex_buffer_data[1638] = 0.5;
  vertex_buffer_data[1639] = 0;
  vertex_buffer_data[1640] = 0;
  vertex_buffer_data[1641] = 0.6;
  vertex_buffer_data[1642] = 0;
  vertex_buffer_data[1643] = 0;
  vertex_buffer_data[1644] = 0.5;
  vertex_buffer_data[1645] = -1;
  vertex_buffer_data[1646] = 0;
  vertex_buffer_data[1647] = 0.6;
  vertex_buffer_data[1648] = 0;
  vertex_buffer_data[1649] = 0;
  vertex_buffer_data[1650] = 0.6;
  vertex_buffer_data[1651] = -1;
  vertex_buffer_data[1652] = 0;
  vertex_buffer_data[1653] = 0.5;
  vertex_buffer_data[1654] = -1;
  vertex_buffer_data[1655] = 0;



  //  static GLfloat vertex_buffer_data_stand2[] = {
  //    0,0,0,
  //    0.2,0,0,
  //    0,-1,0,
  //    0.2,0,0,
  //    0.2,-1,0,
  //    0,-1,0,
  //  };
  //


    this->object = create3DObject(GL_TRIANGLES, 1100, vertex_buffer_data, color, GL_FILL);
    // this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_stand2, color, GL_FILL);
    // this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, color, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Trampoline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


bounding_box_t Trampoline::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float radius = this->radius;
    bounding_box_t bbox = { x, y, radius, 0.4, 0.4 };
    return bbox;
}
