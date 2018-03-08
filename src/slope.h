#include "main.h"

#ifndef SLOPE_H
#define SLOPE_H


class Slope {
public:
    Slope() {}
    Slope(float radius, float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    float radius;
    double speedY;
    double acc;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Slope_H
