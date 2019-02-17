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
#include "para.h"
#include "cannon.h"
#include "gola.h"
#include "alt.h"
#include "bomb.h"
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
vector<Para> para;
vector<Gola> gola;
vector<Cannon> cannon;
vector<Bomb> bomb;
Plane plane;
Score score;
Alt alt;
Health health;
Fuel fuel;
Speed speed;
Sea sea;
vector<Tapu> tapu;
int view = 0;
float camY = -15;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0, degree = 0, radiusB = 0;
float heliX = 0, heliY = 0, heliZ = -10;
double xpos, ypos;
bool barrelRoll = false;
glm::vec3 Axis;
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
    int d1 = 10, d2 = 20;
    // follow cam view
    eye[0] =  glm::vec3 (plane.position.x + (d1*plane.ret[1][0] + d2*plane.ret[2][0]), plane.position.y + (d1*plane.ret[1][1] + d2*plane.ret[2][1]), plane.position.z + (d1*plane.ret[1][2] + d2*plane.ret[2][2]));
    target[0] = glm::vec3 (plane.position.x, plane.position.y, plane.position.z);
    up[0] = glm::vec3 (plane.ret[1][0], plane.ret[1][1], plane.ret[1][2]);
    
    // Top view
    eye[1] =  glm::vec3 (plane.position.x, plane.position.y + 70, plane.position.z);
    target[1] = glm::vec3 (plane.position.x, plane.position.y, plane.position.z);
    up[1] = glm::vec3 (1, 0, 0);    
    
    // plane view
    d1 = 2; d2 = 5; 
    eye[2] =  glm::vec3 (plane.position.x - d2*plane.ret[2][0], plane.position.y - d2*plane.ret[2][1], plane.position.z - d2*plane.ret[2][2]);
    target[2] = glm::vec3 (plane.position.x - 2*d2*plane.ret[2][0], plane.position.y - 2*d2*plane.ret[2][1], plane.position.z - 2*d2*plane.ret[2][2]);
    up[2] = glm::vec3 (plane.ret[1][0], plane.ret[1][1], plane.ret[1][2]);

    // tower view
    eye[3] =  glm::vec3 (plane.position.x + 40, plane.position.y + 50, plane.position.z);
    target[3] = glm::vec3 (plane.position.x, plane.position.y, plane.position.z);
    up[3] = glm::vec3 (-1, 0, 0);
    
    // helicopter cam view
    eye[4] =  glm::vec3 (plane.position.x + heliX/screen_zoom, plane.position.y + heliY/screen_zoom, plane.position.z + heliZ/screen_zoom);
    target[4] = glm::vec3 (plane.position.x, plane.position.y, plane.position.z);
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
    for(auto pr: para)
        pr.draw(VP);
    for(auto cn: cannon)
        cn.draw(VP);
    for(auto tp:tapu)
        tp.draw(VP);
    for(auto vc:volcano)
        vc.draw(VP);
    for(auto gl:gola)
        gl.draw(VP);
    for(auto bm:bomb)
        bm.draw(VP);
    plane.draw(VP);

    // Dashboard
    health.draw(dashVP);
    fuel.draw(dashVP);
    speed.draw(dashVP);
    alt.draw(dashVP);
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
    int v = glfwGetKey(window, GLFW_KEY_V);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int b = glfwGetKey(window, GLFW_KEY_B);
    GLfloat deg = (2*3.1415926/360.0f);
    if(barrelRoll){
        if(degree > 360)
            barrelRoll = false;
        // plane.position.x += 
    }
    if(!barrelRoll){
        degree = 0;
        radiusB = 20.0f;
        Axis = plane.dir + radiusB*plane.up;
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
            plane.position.y += 1.0f;
        }
        if(w){
            plane.speed += plane.acc;
            plane.position.z -= plane.speed*plane.ret[2][2];
            plane.position.y -= plane.speed*plane.ret[2][1];
            plane.position.x -= plane.speed*plane.ret[2][0];
            plane.score += 1;
        }
        plane.speed -= plane.drag;
    }
    if(f and !plane.missileTime){
        plane.missileTime = 1;
        glm::vec3 dir = glm::vec3(plane.ret[2][0],plane.ret[2][1],plane.ret[2][2]);
        missile.push_back(Missile(plane.position.x, plane.position.y, plane.position.z, 0.05, 2.5, dir, plane.ret));
    }
    if(b and !plane.missileTime){
        plane.missileTime = 1;
        glm::vec3 dir = glm::vec3(plane.ret[2][0],plane.ret[2][1],plane.ret[2][2]);
        bomb.push_back(Bomb(plane.position.x, plane.position.y, plane.position.z, 0.5, 1, dir, plane.ret, plane.speed));
    }
    if (v and !plane.timer) {
        view = (view+1)%5;
        plane.timer = 1;
    }
    sea.position.x = plane.position.x;
    sea.position.z = plane.position.z;
    glfwGetCursorPos(window, &xpos, &ypos);
    heliX = (xpos - 300) / 30.0f;
    heliY = (ypos - 300) / 30.0f;
    heliZ = sqrt(200 - heliX*heliX - heliY*heliY);
}

void tick_elements() {
    if(plane.position.y < plane.minAlt)
        exit(0);
    sea.tick();
    for(auto &ms:missile)
        ms.tick();
    for(auto &gl:gola)
        gl.tick();
    for(auto &bm:bomb)
        bm.tick();
    for(auto &cn:cannon){
        cn.tick();
        cn.dir = plane.position - cn.position;
        cn.dir = glm::normalize(cn.dir);
        if(!cn.timer){
            gola.push_back(Gola(cn.position.x, cn.position.y, cn.position.z, 0.5f, 1, cn.dir,cn.rotate));
            cn.timer = 1;
        }
    }
    for(auto tp:tapu)
        tp.tick();
    for(auto vc:volcano)
        vc.tick();
    for(auto pr:para)
        pr.tick();
    plane.tick();
    plane.fuel -= 0.001;
    speed.rot = 135 - plane.speed*270/plane.maxSpeed;
    health.val = plane.health;
    fuel.val = plane.fuel;
    alt.val = plane.position.y;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    score = Score(30, 27);
    health = Health(-29, -28);
    fuel = Fuel(23, -28);
    alt = Alt(23, -20, 105);
    speed = Speed(-23, 25);
    plane = Plane(0, -40, 0, COLOR_RED);
    para.push_back(Para(0, -20, -40, 5));
    sea = Sea(0, -50.0f, 0, 1000, COLOR_SEA);
    tapu.push_back(Tapu(0, -45, -80, 8, COLOR_GREEN));
    tapu.push_back(Tapu(45, -45, -80, 8, COLOR_GREEN));
    cannon.push_back(Cannon(45, -45, -80, 1.0f, 8));
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
