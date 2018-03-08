#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(int flag_player, float radius, float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    int flag_player;
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

#endif // BALL_H
