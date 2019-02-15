#include "main.h"
#include "timer.h"
#include "plane.h"
#include "sea.h"
#include "tapu.h"
#include "volcano.h"
#include "missile.h"
#include "score.h"
#include "health.h"
#include "fuel.h"
#include "speed.h"
using namespace std;

GLMatrices Matrices;
GLMatrices Dash;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

vector<Missile> missile;
vector<Volcano> volcano;
Plane plane;
Score score;
Health health;
Fuel fuel;
Speed speed;
Sea sea;
vector<Tapu> tapu;
int view = 0;
float camY = -15;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

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
    glm::vec3 eye[5];
    glm::vec3 up[5];
    glm::vec3 target[5];

    // follow cam view
    eye[0] =  glm::vec3 (plane.position.x, plane.position.y + 10, plane.position.z + 12);
    // Top view
    eye[1] =  glm::vec3 (plane.position.x, plane.position.y + 70, plane.position.z);
    
    // plane view
    eye[2] =  glm::vec3 (plane.position.x, plane.position.y + 2, plane.position.z-4);
    // tower view
    eye[3] =  glm::vec3 (plane.position.x, plane.position.y + 6, plane.position.z + 10);
    // helicopter cam view
    eye[4] =  glm::vec3 (plane.position.x, plane.position.y + 6, plane.position.z + 10);

    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    target[0] = glm::vec3 (plane.position.x, plane.position.y, plane.position.z -15);
    target[1] = glm::vec3 (plane.position.x, plane.position.y, plane.position.z);
    target[2] = glm::vec3 (plane.position.x, plane.position.y - 2, plane.position.z-10);
    target[3] = glm::vec3 (plane.position.x, plane.position.y, plane.position.z);
    target[4] = glm::vec3 (plane.position.x, plane.position.y, plane.position.z);

    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    up[0] = glm::vec3 (0, 1, 0);
    up[1] = glm::vec3 (1, 0, 0);
    up[2] = glm::vec3 (0, 1, 0);
    up[3] = glm::vec3 (1, 0, 0);
    up[4] = glm::vec3 (1, 0, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye[view], target[view], up[view] ); // Rotating Camera for 3D
    Dash.view = glm::lookAt(glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0,1,0));
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 dashVP = Dash.projection * Dash.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    sea.draw(VP);
    for(auto ms: missile)
        ms.draw(VP);
    for(auto tp:tapu)
        tp.draw(VP);
    for(auto vc:volcano)
        vc.draw(VP);
    plane.draw(VP);
    
    // Dashboard
    health.draw(dashVP);
    fuel.draw(dashVP);
    speed.draw(dashVP);
    int num = plane.score;
    int x = 1;
    while(num>0){
        score.draw(dashVP, num%10, 3*x);
        num /= 10;
        x++;
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int t = glfwGetKey(window, GLFW_KEY_T);
    int f = glfwGetKey(window, GLFW_KEY_F);
    // plane.rotation = glm::vec3(0,0,0);
    GLfloat deg = (2*3.1415926/360.0f);
    if(f and !plane.missileTime){
        plane.missileTime = 1;
        missile.push_back(Missile(plane.position.x, plane.position.y+5, plane.position.z, 0.5, 2));
    }
    if (t and !plane.timer) {
        view = (view+1)%5;
        plane.timer = 1;
    }
    if(up){
        plane.rotation.x = 1.0f;
    }
    if(down){
        plane.rotation.x = -1.0f;
    }
    if(q){
        plane.rotation.y = 1.0f;
    }
    if(e){
        plane.rotation.y = -1.0f;
    }
    if(a){
        plane.rotation.z = 1.0f;
    }
    if(d){
        plane.rotation.z = -1.0f;
    }
    if(space){
        plane.position.y -= plane.speed.y;
    }
    if(w){
        plane.position.z -= plane.speed.z*plane.ret[2][2];
        plane.position.y -= plane.speed.y*plane.ret[2][1];
        plane.position.x -= plane.speed.x*plane.ret[2][0];
        plane.score += 1;
    }
    sea.position.x = plane.position.x;
    sea.position.z = plane.position.z;
}

void tick_elements() {
    sea.tick();
    for(auto &ms:missile)
        ms.tick();
    for(auto tp:tapu)
        tp.tick();
    for(auto vc:volcano)
        vc.tick();
    plane.tick();
    plane.health -= 0.001;
    speed.rot -= 0.1f;
    health.val = plane.health;
    fuel.val = plane.fuel;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    score = Score(30, 27);
    health = Health(-29, -28);
    fuel = Fuel(23, -28);
    speed = Speed(-23, 25);
    plane = Plane(0, -40, 0, COLOR_RED);
    sea = Sea(0, -50.0f, 0, 100, COLOR_SEA);
    tapu.push_back(Tapu(0, -45, -80, 8, COLOR_GREEN));
    volcano.push_back(Volcano(0, -42.5, -80, 5, 10));

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Dash.MatrixID = glGetUniformLocation(programID, "MVP");

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

void reset_screen() {
    float top    = screen_center_y + 30 / screen_zoom;
    float bottom = screen_center_y - 30 / screen_zoom;
    float left   = screen_center_x - 30 / screen_zoom;
    float right  = screen_center_x + 30 / screen_zoom;
    Matrices.projection = glm::perspective(45.0f, (right -left)/(top-bottom), 1.0f, 500.0f);
    Dash.projection = glm::ortho(left, right, bottom, top,0.1f, 1000.0f);
}
