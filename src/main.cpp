#include "main.h"
#include "timer.h"
#include "ball.h"
#include "floor.h"
#include "grass.h"
#include "water.h"
#include "trampoline.h"
#include "porcupine.h"
#include "magnet.h"
#include "slope.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
int score = 0;
Grass grass1;
Water water1;
Floor flor;
Ball ball[50],ball1[50];
Trampoline trampoline1;
Porcupine porcupine1;
Magnet magnet1;
Slope slope[50];
extern double drag_oldx, drag_oldy;
int is_magnet_on = 1, magnet_counter=500;



char scoreput[500];
Ball player;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);




/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
   for(int i=0;i<50;i++){
      slope[i].draw(VP);
   }
   if(is_magnet_on == 0){
    magnet1.draw(VP);
  }
    porcupine1.draw(VP);
    trampoline1.draw(VP);
    grass1.draw(VP);
    flor.draw(VP);
    water1.draw(VP);
    player.draw(VP);
    for(int i=0;i<50;i++)
      ball[i].draw(VP);
      for(int i=0;i<50;i++)
        ball1[i].draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int key_a = glfwGetKey(window, GLFW_KEY_A);
    int key_s = glfwGetKey(window, GLFW_KEY_S);
    int key_d = glfwGetKey(window, GLFW_KEY_D);
    int key_w = glfwGetKey(window, GLFW_KEY_W);
    int mouse_clicked = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if(player.position.x <= 1.7 && player.position.x >= -0.3 && player.position.y <= -1){
      if (left) {
        player.position.x -= 0.02;
      }
      if (right) {
        player.position.x += 0.02;
      }
      if (up) {
        player.speedY = 1;
      }
    }
    else{
      if (left) {
        player.position.x -= 0.05;
      }
      if (right) {
        player.position.x += 0.05;
      }
      if (up) {
        player.speedY = 0.3;
      }
    }

    // zoom in and zoom out
    if (key_a && screen_center_x - 4/screen_zoom > -4) {
        screen_center_x -= 0.07;
        reset_screen();
    }
    if (key_s && screen_center_y - 4/screen_zoom > -4) {
        screen_center_y -= 0.07;
        reset_screen();
    }
    if (key_d && screen_center_x + 4/screen_zoom < 4) {
        screen_center_x += 0.07;
        reset_screen();
    }
    if (key_w && screen_center_y + 4/screen_zoom < 4) {
        screen_center_y += 0.07;
        reset_screen();
    }


    if (mouse_clicked) {
        if (drag_oldx == -1 && drag_oldy == -1) {
            glfwGetCursorPos(window, &drag_oldx, &drag_oldy);
        }
        else {
            int w, h;
            double new_x, new_y;
            glfwGetCursorPos(window, &new_x, &new_y);
            glfwGetWindowSize(window, &w, &h);
            float pos_x, pos_y;
            pos_x = 8 * (new_x - drag_oldx) / (w * screen_zoom);
            player.position.x = pos_x;
        }
    }
}

void tick_elements() {
  magnet_counter--;
  if(magnet_counter >= 0){
    is_magnet_on = 0;

    // magnet condition
    if(player.position.y <= 3.2 && player.position.y >= 2){
      player.position.x -= 0.05;
    }
  }
  else if(magnet_counter < 0){
    is_magnet_on = 1;

    magnet1.tick();
    if(magnet_counter == -500){
      magnet_counter = 500;
    }
  }


 for(int i=0;i<100;i++)
  slope[i].tick();
  porcupine1.tick();
  for(int i=0;i<50;i++){
    ball[i].tick();
  }
  for(int i=0;i<50;i++){
    ball1[i].tick();
  }
  player.tick();


  for(int i=0;i<50;i++){
    if (detect_collision(ball[i].bounding_box(), player.bounding_box()) && player.speedY < 0 && player.position.y > ball[i].position.y ) {
      float x = (float)(-40 + rand() % 20);
      float y = (float)(rand() % 7);
      ball[i].set_position(x,y);
      player.speedY += 0.7;

      // to print the score
      score++;
      cout << score << "\n";
    }
  }


for(int i = 0;i<50;i++){
  if (detect_collision(ball1[i].bounding_box(), player.bounding_box()) && player.speedY < 0 && player.position.y > ball1[i].position.y ) {
    float x = (float)(-40 + rand() % 20);
    float y = (float)(rand() % 7);
    ball1[i].set_position(x,y);
    player.speedY += 0.7;

    // to print the score
    score = score + 2;
    cout << score << "\n";
  }
}

  if(detect_collision_trampoline(player.bounding_box(), trampoline1.bounding_box()) && player.speedY < 0){
    player.speedY += 0.5;
  }


  if(detect_collision_porcupine()) {
    player.set_position(-2,1);
    player.speedY = -0.01;
    porcupine1.set_position(-4,-0.4);
    porcupine1.speed = 0.01;

    // to print the score
    score--;
    cout << score << "\n";
  }



  for(int i=0;i<50;i++){
    if (detect_collision_slope(player.bounding_box(), slope[i].bounding_box()) && player.speedY < 0 && player.position.y >= slope[i].position.y) {
      float x = (float)(-40 + rand() % 20);
      float y = (float)(rand() % 7);
      slope[i].set_position(x,y);
      player.position.x += player.speedY;
      player.speedY = 0.3;
      score = score + 3;
      cout << score << "\n";

    }
  }
  sprintf(scoreput, "Score: %d", score);
  glfwSetWindowTitle(window,scoreput);


}



/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    // slope1 = Slope(0.5,1,1,COLOR_GREEN);
    magnet1 = Magnet(-2,1,COLOR_MAGNET);
    porcupine1 = Porcupine(0,-0.4,COLOR_SILVER);
    trampoline1 = Trampoline(0.6,3,-0.5,COLOR_RED);
    flor = Floor(0,-2,COLOR_BROWN);
    grass1 = Grass(0,-1.5,COLOR_GRASS);
    water1 = Water(1,0.7,-1.45,COLOR_WATER);

    player = Ball(1, 0.5, -2, -1,COLOR_GREEN);
    player.speed = 0;
    player.flag_player=1;
    for(int i=0;i<50;i++){
      float r = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 0.4;
      float x = (float)(-25 + rand() % 20);
      float y = (float)(rand() % 7);
      ball[i]       =  Ball(0,r, x, y, COLOR_RED);
    }

    for(int i=0;i<50;i++){
      float r = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 0.4;
      float x = (float)(-25 + rand() % 20);
      float y = (float)(rand() % 7);
      ball1[i]       =  Ball(0,r, x, y, COLOR_SILVER);
    }

    for(int i=0;i<50;i++){
      float r = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 0.4;
      float x = (float)(-25 + rand() % 20);
      float y = (float)(rand() % 7);
      slope[i]       =  Slope(r, x, y, COLOR_YELLOW);
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

bool detect_collision_slope(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
    // return ((a.x > (b.x-b.radius*sqrt(2))) && (a.x < b.x) && (a.y < (b.y+b.radius*sqrt(2))) && (a.y > b.y)) ;
}

bool detect_collision_trampoline(bounding_box_t a, bounding_box_t b) {
    return (a.x <=  b.x + b.radius + 0.2 && a.x >= b.x - b.radius - 0.2) &&
           (a.y - b.y <= a.radius + 0.6 );
}

int detect_collision_porcupine() {
  float xb = player.position.x;
  float yb = player.position.y;
  float xp = porcupine1.position.x;
  if (xb<=(xp-1.3) && xb>=(xp-2.9) && (yb-player.radius)<=(-1.3)) {
    return 1;
  }
  return 0;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
