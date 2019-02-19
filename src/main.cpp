#include "main.h"
#include "timer.h"
#include "plane.h"
#include "sea.h"
#include "tapu.h"
#include "volcano.h"
#include "mount.h"
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
#include "smoke.h"
#include "compass.h"
#include "fuelup.h"
#include "arrow.h"
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
vector<Mount> mount;
vector<Para> para;
vector<Gola> gola;
Cannon cannon;
Arrow arrow;
vector<Bomb> bomb;
vector<Smoke> smoke;
vector<Fuelup> fuelup;
Plane plane;
Score score;
Compass compass;
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
float aimX = 0, aimY = 0, aimZ = -10;
double xpos, ypos;
bool barrelRoll = false, pause = false, loopingLoop = false;
float loopRot = 0, barrelRot = 0;
glm::vec3 Axis;
bool launchMissile = false, launchBomb = false;
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
    up[4] = glm::vec3 (0, 1, 0);

    arrow.position.x = target[view][0];
    arrow.position.y = target[view][1]+2;
    arrow.position.z = target[view][2];

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
    cannon.draw(VP);
    arrow.draw(VP);
    for(auto tp:tapu)
        tp.draw(VP);
    for(auto vc:volcano)
        vc.draw(VP);
    for(auto mt:mount)
        mt.draw(VP);
    for(auto gl:gola)
        gl.draw(VP);
    for(auto bm:bomb)
        bm.draw(VP);
    for(auto sm:smoke)
        sm.draw(VP);
    for(auto fu:fuelup)
        fu.draw(VP);
    plane.draw(VP);

    // Dashboard
    health.draw(dashVP);
    fuel.draw(dashVP);
    speed.draw(dashVP);
    alt.draw(dashVP);
    compass.draw(dashVP);
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
    int r = glfwGetKey(window, GLFW_KEY_R);
    int p = glfwGetKey(window, GLFW_KEY_P);
    int l = glfwGetKey(window, GLFW_KEY_L);
    if(p){
        pause = true;
    }
    GLfloat deg = (2*3.1415926/360.0f);
    if(barrelRoll){
        barrelRot += 1.0f;
        if(barrelRot >=360){
            barrelRoll = false;
            barrelRot = 0;
        }
        plane.speed = 1.0f;
        plane.rotation.z = 1.0f;
        plane.position.z -= plane.speed*plane.ret[2][2];
        plane.position.y -= plane.speed*plane.ret[2][1];
        plane.position.x -= plane.speed*plane.ret[2][0];
    }
    if(loopingLoop){
        loopRot += 1.0f;
        if(loopRot >=360){
            loopingLoop = false;
            loopRot = 0;
        }
        plane.speed = 1.0f;
        plane.rotation.x = 1.0f;
    }
    if(!barrelRoll and !loopingLoop){
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
        if(r){
            barrelRoll = true;
        }
        if(l){
            loopingLoop = true;
        }
        if(space){
            plane.position.y += 1.0f;
        }
        if(w){
            plane.speed += plane.acc;
            plane.position.z -= plane.speed*plane.ret[2][2];
            plane.position.y -= plane.speed*plane.ret[2][1];
            plane.position.x -= plane.speed*plane.ret[2][0];
        }
        plane.speed -= plane.drag;
    }
    if((f and !plane.missileTime) or launchMissile){
        system("aplay -c 1 -t wav -q ../sound/missile.wav&");
        plane.missileTime = 1;
        launchMissile = false;
        // glm::vec3 dir = glm::vec3(plane.ret[2][0] - aimX, plane.ret[2][1] - aimY, plane.ret[2][2] - aimZ);
        glm::vec3 dir = glm::vec3(plane.ret[2][0],plane.ret[2][1],plane.ret[2][2]);
        dir = glm::normalize(dir);
        missile.push_back(Missile(plane.position.x, plane.position.y, plane.position.z, 0.05, 2.5, dir, plane.ret));
    }
    if((b and !plane.missileTime) or launchBomb){
        launchBomb = false;
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
    if(plane.position.y < plane.minAlt or plane.fuel <= 0 or plane.health <= 0)
        exit(0);
    sea.tick();
    compass.tick(glm::vec3(plane.ret[2][0], plane.ret[2][1], plane.ret[2][2]));
    for(auto &ms:missile)
        ms.tick();
    for(auto &gl:gola)
        gl.tick();
    for(auto &bm:bomb)
        bm.tick();
    // cannon tick
    cannon.tick();
    cannon.dir = plane.position - cannon.position;
    float dis = glm::distance(plane.position, cannon.position);
    cannon.dir = glm::normalize(cannon.dir);
    if(!cannon.timer and dis < 250.0f){
        gola.push_back(Gola(cannon.position.x, cannon.position.y, cannon.position.z, 0.5f, 1, cannon.dir,cannon.rotate));
        cannon.timer = 1;
    }

    // arrow  tick
    arrow.dir = plane.position - cannon.position;
    arrow.dir = glm::normalize(arrow.dir);
    arrow.position = plane.position;

    for(auto tp:tapu)
        tp.tick();
    for(auto vc:volcano)
        vc.tick();
    for(auto &pr:para)
        pr.tick();
    for(auto &sm:smoke)
        sm.tick();
    plane.tick();
    plane.fuel -= 0.0001;
    speed.rot = 135 - plane.speed*270/plane.maxSpeed;
    health.val = plane.health;
    fuel.val = plane.fuel;
    alt.val = plane.position.y;
}

void generateNewObjects()
{
    float posY = 0;
    float posX = 0;
    float posZ = plane.position.z - 100.0f;
    float as = plane.position.x - cannon.position.x;
    as = as / abs(as);

    // clear tapu
    tapu.clear();
    // new smoke rings
    smoke.clear();
    for(int i=0;i<5;i++){
        posX = as * (rand() % 500);
        smoke.push_back(Smoke(50, plane.position.x - posX, posY, posZ, 8, 7, 1));
        posZ -= 100.0f;
    }

    // new mountains
    mount.clear();
    posX = 0;
    posY = -47;
    posZ = plane.position.z - 100.0f;
    for(int i =0;i<5;i++){
        posX = as * (rand() % 500);
        mount.push_back(Mount(plane.position.x - posX, posY, posZ, 10, 20));
        tapu.push_back(Tapu(plane.position.x - posX, posY - 2.5f, posZ, 12, COLOR_GREEN));
        posZ -= 100.0f;
    }

    // new fuelups
    fuelup.clear();
    fuelup.push_back(Fuelup(plane.position.x - as*250, -20, plane.position.z - 250.0f, 3, 2));

    // new parachutes
    posX = 0;
    posY = -20;
    posZ = plane.position.z - 50.0f;
    para.clear();
    for(int i =0;i<10;i++){
        posX = as * (rand() % 500);
        para.push_back(Para(plane.position.x - posX, posY, posZ, 5));
        posZ -= 50.0f;
    }

    // new volcanoes
    volcano.clear();
    posX = 0;
    posY = -47;
    posZ = plane.position.z - 100.0f;
    for(int i =0;i<5;i++){
        posX = as * (rand() % 500);
        volcano.push_back(Volcano(plane.position.x - posX, posY, posZ, 5, 10));
        tapu.push_back(Tapu(plane.position.x - posX, posY - 2.5f, posZ, 8, COLOR_GREEN));
        posZ -= 100.0f;
    }
    
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    // dashboard objects
    score = Score(30, 27);
    health = Health(-29, -28);
    fuel = Fuel(23, -28);
    alt = Alt(23, -20, 105);
    compass = Compass(-26, -5);
    speed = Speed(-23, 25);

    // main objects
    arrow = Arrow(0, -37.5, 0, 1.0f, 2.0f);
    plane = Plane(0, -40, 0, COLOR_RED);
    sea = Sea(0, -50.0f, 0, 1000, COLOR_SEA);
    cannon = Cannon(500, -49.5, -500, 1.0f, 8);
    generateNewObjects();
    tapu.push_back(Tapu(500, -49.5, -500, 8, COLOR_GREEN));
    
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

void checkColissions()
{
    // colission of missile with gola
    for(int i=0;i<missile.size();i++){
        int flag = 0;
        for(int j=0;j<gola.size();j++){
            if(detect_collision(missile[i].bounding_box(), gola[j].bounding_box())){
                flag = 1;
                gola.erase(gola.begin() + j);
                plane.score += 5;
                break;
            }
        }
        if(flag){
            missile.erase(missile.begin() + i);
            break;
        }
    }

    // colission of missile with parachute
    for(int i=0;i<missile.size();i++){
        int flag = 0;
        for(int j=0;j<para.size();j++){
            if(detect_collision(missile[i].bounding_box(), para[j].bounding_box())){
                flag = 1;
                para[j].speed += 0.15f;
                plane.score += 10;
                break;
            }
        }
        if(flag){
            missile.erase(missile.begin() + i);
            break;
        }
    }

    // colission of bomb with parachute
    for(int i=0;i<bomb.size();i++){
        int flag = 0;
        for(int j=0;j<para.size();j++){
            if(detect_collision(bomb[i].bounding_box(), para[j].bounding_box())){
                flag = 1;
                para[j].speed += 0.15f;
                plane.score += 10;
                break;
            }
        }
        if(flag){
            bomb.erase(bomb.begin() + i);
            break;
        }
    }

    // colission of bomb with cannon
    for(int i=0;i<bomb.size();i++){
        if(detect_collision(bomb[i].bounding_box(), cannon.bounding_box())){
            cannon.position.z -= 500.0f;
            cannon.position.x += 500.0f * (rand()%2?1:-1);
            system("aplay -c 1 -t wav -q ../sound/cannon.wav&");
            generateNewObjects();
            tapu.push_back(Tapu(cannon.position.x, cannon.position.y, cannon.position.z, 8, COLOR_GREEN));
            plane.score += 100;
            bomb.erase(bomb.begin() + i);
            break;
        }
    }

    // colission of gola with plane
    for(int i=0;i<gola.size();i++){
        if(detect_collision(plane.bounding_box(),gola[i].bounding_box())){
            gola.erase(gola.begin() + i);
            plane.health -= 0.1f;
            break;
        }
    }

    // colission of plane with smoke rings
    for(int i=0;i<smoke.size();i++){
        if(detect_collision(plane.bounding_box(), smoke[i].bounding_box())){
            if(smoke[i].timer)
                break;
            plane.score += 50;
            smoke[i].timer = 1;
            break;
        }
    }

    // colission of plane with parachute
    for(int j=0;j<para.size();j++){
        if(detect_collision(plane.bounding_box(), para[j].bounding_box())){
            para[j].speed += 0.15f;
            plane.health -= 0.05f;
            break;
        }
    }

    // colission of plane with volcanoes
    for(int j=0;j<volcano.size();j++){
        if(detect_collision(plane.bounding_box(), volcano[j].bounding_box())){
            plane.health = 0.0f;
            break;
        }
    }

    // colission of plane with mountains
    for(int j=0;j<mount.size();j++){
        if(detect_collision(plane.bounding_box(), mount[j].bounding_box())){
            plane.health = 0.0f;
            break;
        }
    }

    // colission of plane with fuel ups
    for(int j=0;j<fuelup.size();j++){
        if(detect_collision(plane.bounding_box(), fuelup[j].bounding_box())){
            fuelup.erase(fuelup.begin()+j);
            plane.fuel = 1.00f;
            break;
        }
    }
}
void deleteObjects()
{
    // delete missiles
    for(int i=0;i<missile.size();i++){
        float x = glm::distance(missile[i].position, plane.position);
        if(x > 200){
            missile.erase(missile.begin()+i);
            break;
        }
    }
    // delete bomb
    for(int i=0;i<bomb.size();i++){
        float x = glm::distance(bomb[i].position, plane.position);
        if(x > 200){
            bomb.erase(bomb.begin()+i);
            break;
        }
    }
    // delete gola
    for(int i=0;i<gola.size();i++){
        float x = glm::distance(gola[i].position, plane.position);
        if(x > 200){
            gola.erase(gola.begin()+i);
            break;
        }
    }
    // delete parachute
    for(int i=0;i<para.size();i++){
        if(para[i].position.y < -60.0f){
            para.erase(para.begin()+i);
            break;
        }
    }
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
            int o = glfwGetKey(window, GLFW_KEY_O);
            if(o){
                pause = false;
            }
            else if (!pause){
                // OpenGL Draw commands
                draw();
                // Swap Frame Buffer in double buffering
                glfwSwapBuffers(window);
                checkColissions();
                deleteObjects();
                tick_elements();
                tick_input(window);
            }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.depth + b.depth)) ;
}

void reset_screen() {
    float top    = screen_center_y + 30;
    float bottom = screen_center_y - 30;
    float left   = screen_center_x - 30;
    float right  = screen_center_x + 30;
    Matrices.projection = glm::perspective(45.0f, (right -left)/(top-bottom), 1.0f, 500.0f);
    Dash.projection = glm::ortho(left, right, bottom, top,0.1f, 1000.0f);
}
