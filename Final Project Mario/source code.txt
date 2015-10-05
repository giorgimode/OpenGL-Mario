//////////////////////////////Giorgi Modebadze/////////////////////////////
///////////////////////////////ID: 100071281/////////////////////////////
/////////////////////////////// COS 397 Computer Graphics/////////////////////////////
///////////////////////////////Course Project/////////////////////////////
/////////////////////////////// American Univeristy in Bulgaria/////////////////////////////
/////////////////////////////// Spring semester 2013/////////////////////////////
///////////////////////// Professor Svetla Boytcheva///////////////////////
///////////////////////Music from Super Mario game, developed by Nintendo, composed by Koji Kondo///////////////////////
///////////////////////Texture in room are screenshots from Mario Game, licensed to Nintendo///////////////////////

#include <GL/glfw.h>
using namespace std;
#include <cstdlib>
#include <math.h>
#include <time.h>
#include "cos397lib.h"
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <audiere.h>
using namespace audiere;
 OutputStreamPtr sound;
 float volume=0.9f;
float t = 0;

int na = 16;


    GLuint textureA,textureB,textureC,textureD, textureF;
// Draw shadow of the bouncing mushroom
    void drawSolidCircleXY( float x, float y, float z, float r )
{
    float alpha = 0.0;
    float dalpha = 2*M_PI/na;

    glBegin( GL_POLYGON );
    for( int i=0; i<na; i++)
    {
        glVertex3f( x+r*cos(alpha), y+r*sin(alpha), z );
        alpha += dalpha;
    }
    glEnd();
}

// Draw Room
void drawTexturedCube()
{
    float a = 15;

 glBindTexture(GL_TEXTURE_2D,textureA);   //walls

    glBegin( GL_QUADS );       // -x
        glNormal3f(+a, -a, -a);
        glTexCoord2f(0, 0);
        glVertex3f(-3*a, -5*a, -a);
        glNormal3f(+a, -a, +a);
        glTexCoord2f(0, 1);
        glVertex3f(-3*a, -5*a, +a);
        glNormal3f(+a, +a, +a);
        glTexCoord2f(1, 1);
        glVertex3f(-3*a, +5*a, +a);
        glNormal3f(+a, +a, -a);
        glTexCoord2f(1, 0);
        glVertex3f(-3*a, +5*a, -a);

        glNormal3f(-a, -a, -a);  // +x
        glTexCoord2f(0, 0);
        glVertex3f(+3*a, -5*a, -a);
        glNormal3f(-a, -a, +a);
        glTexCoord2f(0, 1);
        glVertex3f(+3*a, -5*a, +a);
        glNormal3f(-a, +a, +a);
        glTexCoord2f(1, 1);
        glVertex3f(+3*a, +5*a, +a);
        glNormal3f(-a, +a, -a);
        glTexCoord2f(1, 0);
        glVertex3f(+3*a, +5*a, -a);

                glNormal3f(-a, -a, -a);   // +y
        glTexCoord2f(0, 0);
        glVertex3f(-3*a, +5*a, -a);
        glNormal3f(-a, -a, +a);
        glTexCoord2f(0, 1);
        glVertex3f(-3*a, +5*a, +a);
        glNormal3f(+a, -a, +a);
        glTexCoord2f(1, 1);
        glVertex3f(+3*a, +5*a, +a);
        glNormal3f(+a, -a, -a);
        glTexCoord2f(1, 0);
        glVertex3f(+3*a, +5*a, -a);

     glEnd();


glBindTexture(GL_TEXTURE_2D,textureD);
glBegin( GL_QUADS );

        glNormal3f(-a, +a, -a);  // -y
        glTexCoord2f(0, 0);
        glVertex3f(-3*a, -5*a, -a);
        glNormal3f(-a, +a, +a);
        glTexCoord2f(0, 1);
        glVertex3f(-3*a, -5*a, +a);
        glNormal3f(+a, +a, +a);
        glTexCoord2f(1, 1);
        glVertex3f(+3*a, -5*a, +a);
        glNormal3f(+a, +a, -a);
        glTexCoord2f(1, 0);
        glVertex3f(+3*a, -5*a, -a);
   glEnd();


   glBindTexture(GL_TEXTURE_2D,textureB);  //ceiling
  glBegin( GL_QUADS );
        glNormal3f(-a, -a, -a);
        glTexCoord2f(0, 0);
        glVertex3f(-3*a, -5*a, +a);
        glNormal3f(-a, +a, -a);
        glTexCoord2f(0, 3);
        glVertex3f(-3*a, +5*a, +a);
        glNormal3f(+a, +a, -a);
        glTexCoord2f(3, 3);
        glVertex3f(+3*a, +5*a, +a);
        glNormal3f(+a, -a, -a);
        glTexCoord2f(3, 0);
        glVertex3f(+3*a, -5*a, +a);
glEnd();


glBindTexture(GL_TEXTURE_2D,textureC);  //floor

  glBegin( GL_QUADS );
        glNormal3f(-a, -a, +a);
        glTexCoord2f(0, 0);
         glVertex3f(-3*a, -5*a, -a);
        glNormal3f(-a, +a, +a);
        glTexCoord2f(0, 2);
        glVertex3f(-3*a, +5*a, -a);
        glNormal3f(+a, +a, +a);
        glTexCoord2f(2, 2);
        glVertex3f(+3*a, +5*a, -a);
        glNormal3f(+a, -a, +a);
        glTexCoord2f(2, 0);
        glVertex3f(+3*a, -5*a, -a);
    glEnd();

}

//Draw Mario-style carnivorous plants in wells
void drawPlants(float x, float y, float z)
{   glColor3ub(127, 255, 0);
    drawSolidCylinder(x, y, z, 5, 10, 40);
    drawSolidCylinder(x, y, z+10, 6, 4, 40);


    COS397_POINT pstart1, pend1;
    pstart1.x=x;
    pstart1.y=y-2;
    pstart1.z=z+14;

    pend1.x=x-5;
    pend1.y=y-2;
    pend1.z=z+20;

 glColor3ub(255, 106, 106);

    drawSlopedSmoothEllipsoid(pstart1, pend1, 1.7, 1 );

     COS397_POINT pstart2, pend2;
    pstart2.x=x;
    pstart2.y=y-2;
    pstart2.z=z+14;

    pend2.x=x+5;
    pend2.y=y-2;
    pend2.z=z+20;

drawSlopedSmoothEllipsoid(pstart2, pend2, 1.7, 1 );
drawWall(x, y-2, z+18, 0.01, 1, 3);
glColor3ub(255, 255, 255);
//glColor3ub(0, 205, 0);
//drawSmoothEllipsoidPatch(x, y-2, z+22, 3, 3, 3, 0, 2*M_PI,  5*M_PI/6, 2*M_PI );
glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D,textureF);  //
drawTextureEllipsoidPatch(x, y-2, z+22, 3, 3, 3, 0, 2*M_PI,  5*M_PI/6, 2*M_PI );  //plant head
glDisable(GL_TEXTURE_2D);

}


// Columns in the room
void drawColumns(){
 float a=12;

glColor3ub(135, 206, 255);
            drawTruncatedCone(30, 65, -15, 6, 4, 10, 10);
            drawTruncatedCone(30, 65, -14, 4, 3, 86, 10);
            drawSolidCylinder(30, 65, 7, 4, 2, 10 );
            drawSolidSphere(30, 65, 11, 3);
            drawSolidCylinder(30, 65, 13, 4, 2, 10 );

            drawTruncatedCone(30, 25, -15, 6, 4, 10, 10);
            drawTruncatedCone(30, 25, -14, 4, 3, 86, 10);
            drawSolidCylinder(30, 25, 7, 4, 2, 10 );
            drawSolidSphere(30, 25, 11, 3);
            drawSolidCylinder(30, 25, 13, 4, 2, 10 );

            drawTruncatedCone(30, -25, -15, 6, 4, 10, 10);
            drawTruncatedCone(30, -25, -14, 4, 3, 86, 10);
            drawSolidCylinder(30, -25, 7, 4, 2, 10 );
            drawSolidSphere(30, -25, 11, 3);
            drawSolidCylinder(30, -25, 13, 4, 2, 10 );

             drawTruncatedCone(30, -65, -15, 6, 4, 10, 10);
            drawTruncatedCone(30, -65, -14, 4, 3, 86, 10);
            drawSolidCylinder(30, -65, 7, 4, 2, 10 );
            drawSolidSphere(30, -65, 11, 3);
            drawSolidCylinder(30, -65, 13, 4, 2, 10 );


            drawTruncatedCone(-30, 65, -15, 6, 4, 10, 10);
            drawTruncatedCone(-30, 65, -14, 4, 3, 86, 10);
            drawSolidCylinder(-30, 65, 7, 4, 2, 10 );
            drawSolidSphere(-30, 65, 11, 3);
            drawSolidCylinder(-30, 65, 13, 4, 2, 10 );

            drawTruncatedCone(-30, 25, -15, 6, 4, 10, 10);
            drawTruncatedCone(-30, 25, -14, 4, 3, 86, 10);
            drawSolidCylinder(-30, 25, 7, 4, 2, 10 );
            drawSolidSphere(-30, 25, 11, 3);
            drawSolidCylinder(-30, 25, 13, 4, 2, 10 );

            drawTruncatedCone(-30, -25, -15, 6, 4, 10, 10);
            drawTruncatedCone(-30, -25, -14, 4, 3, 86, 10);
            drawSolidCylinder(-30, -25, 7, 4, 2, 10 );
            drawSolidSphere(-30, -25, 11, 3);
            drawSolidCylinder(-30, -25, 13, 4, 2, 10 );

             drawTruncatedCone(-30, -65, -15, 6, 4, 10, 10);
            drawTruncatedCone(-30, -65, -14, 4, 3, 86, 10);
            drawSolidCylinder(-30, -65, 7, 4, 2, 10 );
            drawSolidSphere(-30, -65, 11, 3);
            drawSolidCylinder(-30, -65, 13, 4, 2, 10 );






}




class ventilation{
 private: float x,y,z,r,h, alpha, beta;
          int n;  //number of blades

 public:
    ventilation (float x1, float y1, float z1, float r1, float h1)
    {
        x=x1;y=y1;z=z1;r=r1;h=h1;
        alpha=beta=0;
        n=3;
    }

void set_alpha(float a)
{
    alpha=a;
}

void set_beta(float b)
{
    beta=b;
}

void drawBlade()
{
     float rx=r/20 , ry=5*r/n, rz=5*r-.2;
     float dbeta = 2*M_PI/n;
     float bb=beta;
     COS397_POINT pcent = {x,y,z+h+r/2+h*8+r/2-0.2  };

    glPushMatrix();

    glTranslatef(r+1,0,0);
    for (int i=0; i<n; i++)
      {
        COS397_POINT pend= {pcent.x,pcent.y+2*rz*cos(bb),pcent.z+2*rz*sin(bb)};
        drawSlopedSmoothEllipsoid(pcent,pend,rx,ry);
        bb+=dbeta;
      }
    glPopMatrix();

}

void drawBody()
{
 COS397_POINT p0={x,y,z+h+r/2+h*8+r/2-0.2};
    COS397_POINT p1={x+r+1.5,y,z+h+r/2+h*8+r/2-0.2};
    drawSlopedSolidHollowCylinder(p0,p1,3*r/2);
    COS397_POINT p2={x-r,y,z+h+r/2+h*8+r/2-0.2};
    drawSmoothEllipsoidPatch(p1.x,p1.y,p1.z,r/2,r/2,r/2,M_PI+M_PI/2,2*M_PI+M_PI/2,-M_PI,M_PI );
    drawSlopedSolidHollowCylinder(p0,p2,r/2);
    //drawSmoothEllipsoidPatch(p2.x,p2.y,p2.z,r/4,r/2,r/2,M_PI/2,3*M_PI/2,-M_PI,M_PI );
drawSmoothEllipsoidPatch(p1.x,p1.y,p1.z, 1.5*r, 1.5*r, 1.5*r,M_PI+M_PI/2,2*M_PI+M_PI/2,-M_PI,M_PI );
}


void drawVentilation()
{  // drawBase();
glColor3ub(121, 205, 205);
    drawBody();
    drawBlade();
glColor3ub(255, 255, 255);

   glEnable(GL_LIGHTING);
}

void drawReflexion()    // ventilation reflection
{
glColor4ub(121, 205, 205, 130);
glPushMatrix();
glTranslatef(x, y, z);
glRotatef(0, 0, 0, 1);       //Rotate about the y-axis
glTranslatef(-x-2, -y, -z);


drawBody();
    drawBlade();
  //drawVentilation();
   glColor3ub(120, 100, 100);
  glPopMatrix();

 glColor4f(1,1,1,1);
}


};

//draw the round base of ventilation
void drawVentBase(float x, float y, float z)
{
  glPushMatrix();
    glRotatef(90,0,1,0);

 glColor3ub(139, 134, 130);

  drawSolidCylinder(x , y, z-2.4, 10, 1.5, 40);

glColor4ub(139, 134, 130,250);
 drawSolidCylinder(x , y, z-1, 10, 2, 40);
    glPopMatrix();
    glColor4f(1,1,1,1);


//43,-44, -2
}

// draw bouncing mushroom with texture
void drawMushroom(float x, float y, float z, float rx, float ry, float rz)
{
    drawTextureEllipsoidPatch(x, y, z-10, rx, ry, rz-.4, 0, 2*M_PI, M_PI, -M_PI/4);

}

// draw the box for mushroom

void drawBox(float x, float y, float z, float size)
{ float a=size;

glColor3ub(34, 139, 34);
  glBegin( GL_QUADS );                    // +y - left
        glNormal3f(0.0, +1.0, 0.0);
        glVertex3f(x-a, y+a, z-a);
        glVertex3f(x-a, y+a, z-2.82*a);
        glVertex3f(x-a+2.6, y+a, z-2.82*a);
        glVertex3f(x-a+2.6, y+a, z-a);
    glEnd();

    glBegin( GL_QUADS );                // -x - right
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(x-a, y+a, z-a);
        glVertex3f(x-a, y+a, z-2.82*a);
        glVertex3f(x-a, y+a-2.6, z-2.82*a);
        glVertex3f(x-a, y+a-2.6, z-a);
    glEnd();

glBegin( GL_QUADS );                    // +y - right
        glNormal3f(0.0, +1.0, 0.0);
        glVertex3f(x+a, y+a, z-a);
        glVertex3f(x+a, y+a, z-2.82*a);
        glVertex3f(x+a-2.6, y+a, z-2.82*a);
        glVertex3f(x+a-2.6, y+a, z-a);
    glEnd();

    glBegin( GL_QUADS );                // -x - right
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y-a, z-2.82*a);
        glVertex3f(x-a, y-a+2.6, z-2.82*a);
        glVertex3f(x-a, y-a+2.6, z-a);
    glEnd();

    glBegin( GL_QUADS );                // +x - left
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(x+a, y+a, z-a);
        glVertex3f(x+a, y+a, z-2.82*a);
        glVertex3f(x+a, y+a-2.6, z-2.82*a);
        glVertex3f(x+a, y+a-2.6, z-a);
    glEnd();

    glBegin( GL_QUADS );                // +x - right
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(x+a, y-a, z-a);
        glVertex3f(x+a, y-a, z-2.82*a);
        glVertex3f(x+a, y-a+2.6, z-2.82*a);
        glVertex3f(x+a, y-a+2.6, z-a);
    glEnd();

    glBegin( GL_QUADS );                    // -y - left
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y-a, z-2.82*a);
        glVertex3f(x-a+2.6, y-a, z-2.82*a);
        glVertex3f(x-a+2.6, y-a, z-a);
    glEnd();

glBegin( GL_QUADS );                    // -y - right
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(x+a, y-a, z-a);
        glVertex3f(x+a, y-a, z-2.82*a);
        glVertex3f(x+a-2.6, y-a, z-2.82*a);
        glVertex3f(x+a-2.6, y-a, z-a);
    glEnd();


  glBegin( GL_QUADS );
                                    // top glass
        glNormal3f(0.0, 1.0, 0.0);
glColor4ub(34, 139, 34, 155);
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y+a, z-a);
        glVertex3f(x+a, y+a, z-a);
        glVertex3f(x+a, y-a, z-a);
    glEnd();

 glBegin( GL_QUADS );
                                        // front glass
        glNormal3f(0.0, -1.0, 0.0);
glColor4ub(250, 128, 114, 80);
        glVertex3f(x-a+2.6, y-a, z-a);
        glVertex3f(x-a+2.6, y-a, z-3*a);
        glVertex3f(x+a-2.6, y-a, z-3*a);
        glVertex3f(x+a-2.6, y-a, z-a);
    glEnd();

    glBegin( GL_QUADS );
                                        // back glass
        glNormal3f(0.0, 1.0, 0.0);
glColor4ub(250, 128, 114, 80);
        glVertex3f(x-a+2.6, y+a, z-a);
        glVertex3f(x-a+2.6, y+a, z-3*a);
        glVertex3f(x+a-2.6, y+a, z-3*a);
        glVertex3f(x+a-2.6, y+a, z-a);
    glEnd();

glBegin( GL_QUADS );
        glNormal3f(-1.0, 0.0, 0.0);      // right glass
glColor4ub(250, 128, 114, 80);
        glVertex3f(x-a, y+a-2.6, z-a);
        glVertex3f(x-a, y+a-2.6, z-3*a);
          glVertex3f(x-a, y-a+2.6, z-3*a);
        glVertex3f(x-a, y-a+2.6, z-a);

    glEnd();


glBegin( GL_QUADS );
        glNormal3f(1.0, 0.0, 0.0);      // left glass
glColor4ub(250, 128, 114, 80);
        glVertex3f(x+a, y+a-2.6, z-a);
        glVertex3f(x+a, y+a-2.6, z-3*a);
          glVertex3f(x+a, y-a+2.6, z-3*a);
        glVertex3f(x+a, y-a+2.6, z-a);

    glEnd();

}





float rotTime,rotTime1, rotTime2, rotTime3;

// Calculating point from Lemniscate of Bernoulli

COS397_POINT lemniscateOfBernoulli(float rotTime)
{
    COS397_POINT r;
   // float s = sin(t);
  //  float c = cos(t);
    r.x = rotTime;
    r.y = 9*rotTime;
    r.z = 2;
    return r;
}

// variables for mouse movement
float ma;    // Current horizontal angle
float mb;    // Current vertical angle

bool dragging = false; // Flag for active rotation

int xpos = 0;   // Current postion of
int ypos = 0;   // mouse - x and y coordinates


// Called when mouse button is pushed on/off
void GLFWCALL onMouseButton( int button, int action )
{
    if( button==GLFW_MOUSE_BUTTON_LEFT )
    {
        dragging = action==GLFW_PRESS;
        glfwGetMousePos( &xpos, &ypos );
    }
}

// Called on  mouse move
void GLFWCALL onMouseMove( int mx, int my )
{
    if( dragging )
    {
        ma = ma-(mx-xpos)/150.0;
        mb = mb+(my-ypos)/150.0;
        if( mb>+1.5 ) mb=+1.5;
        if( mb<-1.5 ) mb=-1.5;
        xpos = mx;
        ypos = my;
    }
}

int main()
{
    init();

 string filename="mario.mp3";
       AudioDevicePtr device = OpenDevice();
     OutputStreamPtr sound1(OpenSound(device, filename.c_str(), false));

string filename2="creepy.mp3";

        OutputStreamPtr sound2(OpenSound(device, filename2.c_str(), false));


//    glfwSetKeyCallback( onKey );

 glfwSetMouseButtonCallback( onMouseButton );
    glfwSetMousePosCallback( onMouseMove );

    glClearColor( 0,0,0,0 );
    glEnable( GL_DEPTH_TEST );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_NORMALIZE );

	glShadeModel(GL_SMOOTH);

    glColor3f(1,1,1);

    // Loading and activating textures
       glEnable( GL_NORMALIZE );
       glEnable(GL_BLEND);
       glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


    glEnable(GL_TEXTURE_2D);

    glGenTextures(1,&textureA);
    glBindTexture(GL_TEXTURE_2D,textureA);
    glfwLoadTexture2D("wallpaper.tga", GLFW_BUILD_MIPMAPS_BIT);

   glGenTextures(1,&textureB);
    glBindTexture(GL_TEXTURE_2D,textureB);
    glfwLoadTexture2D("ceiling.tga", GLFW_BUILD_MIPMAPS_BIT);

glGenTextures(1,&textureC);
   glBindTexture(GL_TEXTURE_2D,textureC);
   glfwLoadTexture2D("floor.tga", GLFW_BUILD_MIPMAPS_BIT);

glGenTextures(1,&textureD);
      glBindTexture(GL_TEXTURE_2D,textureD);
   glfwLoadTexture2D("door.tga", GLFW_BUILD_MIPMAPS_BIT);

glGenTextures(1,&textureF);
      glBindTexture(GL_TEXTURE_2D,textureF);
   glfwLoadTexture2D("mushroom.tga", GLFW_BUILD_MIPMAPS_BIT);


     glLoadIdentity();

ventilation Ventilation1(-43,-44, -2,1,0.1);

ventilation Ventilation2(-13,-44, -2,1,0.1);

ventilation Ventilation3(-43,0, -2,1,0.1);
ventilation Ventilation5(-43,44, -2,1,0.1);
ventilation Ventilation4(-13,-88, -2,1,0.1);
ventilation Ventilation6(-13,-132, -2,1,0.1);

float a=0;
float da =0.01;
float b=0;
float db =0.3;

COS397_POINT v = {random(0.005,0.02),random(0.005,0.02),random(0.005,0.02)};
    COS397_POINT p = {random(-3,3),random(-3,3),random(-3,3)};

    float size = 9;
    float radius = 2.5;
    float limit = size-radius;

//Makes a room a little brighter
GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);


    srand(time(NULL));
 rotTime =0; // variables for navigation
 rotTime1=0;
 rotTime2=0;
 rotTime3=0;
ma=0; mb=0;
    while( running() )
    {
        glClear( GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT );
         glLoadIdentity();
//navigation --------------------------------------------
        COS397_POINT erti = lemniscateOfBernoulli(rotTime);
        COS397_POINT ori = lemniscateOfBernoulli(rotTime+0.4);


    if (erti.y-70<35)  { rotTime = rotTime + .1; gluLookAt( -25,erti.y-70,3,    -25,ori.y-70,   3, 0,0,1);}   // left

float lookatX1=-25+rotTime/100;
float lookatY1=40-rotTime/100;
float lookatX2=23-rotTime1/100;
float lookatY2=35-rotTime1/100;
float lookatX3=16-rotTime2/100;
float lookatY3=-55+rotTime2/100;
float lookatX4=-5+rotTime3/100;
float lookatY4=-45+rotTime3/100;
     if (erti.y-70>=35 && lookatY1>35 )   {   gluLookAt( -25, 35 , 3,   lookatX1, lookatY1,3,         0,0,1);    rotTime=rotTime+10;}  //front left corner
      //  if (lookatY=35) rotTime=0;
     if (lookatY1<=35 && lookatX1<20)   { gluLookAt( lookatX1-4, 35,3,    25, 35, 3,      0,0,1); rotTime=rotTime+80;}  //front
   if (lookatX1>=20 && lookatX2>16)   {   gluLookAt( 16, 35, 3,   lookatX2, lookatY2,3,         0,0,1); rotTime1=rotTime1+20;   }  //front right corner
if ( lookatX2<=16 && lookatY2>=-50) {   gluLookAt( 16, lookatY2+5, 3,   16, -70,3,         0,0,1); rotTime1=rotTime1+80;   }  //right
if ( lookatY2<-50 && lookatY3<-45 ) {   gluLookAt( 16, -45, 3,   lookatX3, lookatY3,3,         0,0,1); rotTime2=rotTime2+30;   }       // back left corner
if (  lookatY3>=-45 && lookatX3> -5 ) {   gluLookAt( lookatX3+10, -45, 3,   -16, -45,3,         0,0,1); rotTime2=rotTime2+50;   }       // back
if (lookatX3<= -5 && lookatX4<=5)   {   gluLookAt( 5, -45, 3,   lookatX4, lookatY4,3,         0,0,1); rotTime3=rotTime3+20;   }       // back
if (lookatX4<5) {

 sound=sound1;

     sound->play();
     sound->setRepeat(true);
     sound->setVolume(volume);


}
if ( lookatX4==5)   sound->stop();
if ( lookatX4>5)   {
                      //  gluLookAt( 5, -45, 3,   5, 45,3,         0,0,1);
                        gluLookAt( 35*sin(ma)*cos(mb),-35*cos(ma)*cos(mb),10*sin(mb)+3, 0, 0,0, 0,0,1);

                         sound=sound2;

     sound->play();
     sound->setRepeat(true);
     sound->setVolume(volume);

                        }
// --------------------------------------------------------------------------------------------------------------


glEnable(GL_TEXTURE_2D);
    // drawing the room
    glColor3f(1,1,1);
drawTexturedCube();
glDisable(GL_TEXTURE_2D);


 drawColumns();

drawPlants(-10, 65, -15);
drawPlants(10, 65, -15);
//glEnable(GL_BLEND);

drawVentBase(0.5,-44, -44);
drawVentBase(0.5,0, -44);
drawVentBase(0.5,44, -44);

Ventilation1.set_alpha(a);
Ventilation1.set_beta(b);
Ventilation2.set_alpha(a);
Ventilation2.set_beta(b);
Ventilation3.set_alpha(a);
Ventilation3.set_beta(b);
Ventilation4.set_alpha(a);
Ventilation4.set_beta(b);
Ventilation5.set_alpha(a);
Ventilation5.set_beta(b);
Ventilation6.set_alpha(a);
Ventilation6.set_beta(b);


 Ventilation1.drawReflexion();
 Ventilation3.drawReflexion();
 Ventilation5.drawReflexion();
//    glColor3f(0.2,0.2,0.2);


Ventilation1.drawVentilation();
Ventilation3.drawVentilation();
Ventilation5.drawVentilation();
// drawing ventilation on the opposite wall
  glPushMatrix();
    glTranslatef(15,-44, -2);
glRotatef(180, 0, 0, 1);       //Rotate about the y-axis
glTranslatef(-15,44, 2);
drawVentBase(0.5,-44, -14);
drawVentBase(0.5, -88, -14);
drawVentBase(0.5, -132, -14);
 Ventilation2.drawVentilation();
 Ventilation2.drawReflexion();
  Ventilation4.drawVentilation();
 Ventilation4.drawReflexion();
   Ventilation6.drawVentilation();
 Ventilation6.drawReflexion();
    glPopMatrix();

//----------------------------
// drawing bouncing ball
a+=da;
b+=db;
     float s=55; //speed of ball
        // New position calculation
        p.x = p.x+s*v.x;
        p.y = p.y+s*v.y;
        p.z = p.z+s*v.z;

        // Direction reverse
        if( fabs(p.x)>=limit-.1 ) v.x = -v.x;
        if( fabs(p.y)>=limit-.1 ) v.y = -v.y;
        if( ((p.z)>=limit-1) || ((p.z)<=-limit+5.8) ) v.z = -v.z;

glColor3ub(255,255,255);
        drawSolidCylinder(p.x, p.y, p.z-12.5, radius-.5, 2.5, 40);

        drawSmoothEllipsoidPatch(p.x, p.y, p.z-12.5, radius-.5, radius-.5, radius/2, 0, 2*M_PI, M_PI, -M_PI/4);

  glPushMatrix();

  glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D,textureF);

drawMushroom(p.x, p.y, p.z, radius, radius, radius);

glPopMatrix();

// Drawing shadow of the mushroom
        glColor3ub(55,55,10);

        drawSolidCircleXY( p.x, p.y-.3, -size/2.0-10, radius-.4 );
glDisable(GL_TEXTURE_2D);
drawBox(0,0, 7,size); // draw box for bouncing mushroom


        glfwSwapBuffers();
    }

    finit();
    sound->stop();
    return 0;
}

