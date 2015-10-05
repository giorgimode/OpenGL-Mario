#include <cstdlib>
#include <math.h>
#include <GL/glfw.h>
#include "cos397lib.h"

float random(float a, float b)
{
    return (rand()/(float)RAND_MAX)*(b-a)+a;
}

bool running()
{
    return( !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED) );
}

void init()
{
    int width, height;

    glfwInit();
    if( !glfwOpenWindow( 640, 480, 0, 0, 0, 0, 8, 0, GLFW_FULLSCREEN ) ) return;

    glfwGetWindowSize( &width, &height );
    height = height > 0 ? height : 1;

    glViewport( 0, 0, width, height );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 65.0f, (GLfloat)width/(GLfloat)height, 1.0f, 150.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(0.0f, -3.0f, 3.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f );
}

void finit()
{
    glfwTerminate();
}

void drawCube (float x,float y,float z,float a)
{
    a = a/2;
    glBegin( GL_LINE_LOOP );
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y-a, z+a);

        glVertex3f(x+a, y-a, z+a);
        glVertex3f(x+a, y-a, z-a);
    glEnd();

    glBegin( GL_LINE_LOOP );
        glVertex3f(x-a, y+a, z-a);
        glVertex3f(x-a, y+a, z+a);

        glVertex3f(x+a, y+a, z+a);
        glVertex3f(x+a, y+a, z-a);
    glEnd();

    glBegin( GL_LINES );
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y+a, z-a);

        glVertex3f(x-a, y-a, z+a);
        glVertex3f(x-a, y+a, z+a);

        glVertex3f(x+a, y-a, z+a);
        glVertex3f(x+a, y+a, z+a);

        glVertex3f(x+a, y-a, z-a);
        glVertex3f(x+a, y+a, z-a);
    glEnd();
}

void drawOxyz()
{
    // Drawing axis
    glBegin( GL_LINES );
        // OX
        glVertex3f( 0.0, 0.0, 0.0 );
        glVertex3f( 5.0, 0.0, 0.0 );
        // OY
        glVertex3f( 0.0, 5.0, 0.0 );
        glVertex3f( 0.0, 0.0, 0.0 );
        // OZ
        glVertex3f( 0.0, 0.0, 5.0 );
        glVertex3f( 0.0, 0.0, 0.0 );
    glEnd();

    // Drawing arrows
    glBegin( GL_TRIANGLES );
        // OX
        glVertex3f( 5.0, 0.0, 0.0 );
        glVertex3f( 4.5, 0.2, 0.0 );
        glVertex3f( 4.5,-0.2, 0.0 );
        // OY
        glVertex3f( 0.0, 5.0, 0.0 );
        glVertex3f( 0.2, 4.5, 0.0 );
        glVertex3f(-0.2, 4.5, 0.0 );
        // OZ
        glVertex3f( 0.0,  0.0,  5.0 );
        glVertex3f(+0.14,-0.14, 4.5 );
        glVertex3f(-0.14,+0.14, 4.5 );
    glEnd();
}

COS397_POINT point( float x, float y, float z)
{
    COS397_POINT p;
    p.x = x;
    p.y = y;
    p.z = z;
    return( p );
}

float distance( COS397_POINT a, COS397_POINT b)
{
    float dx = a.x-b.x;
    float dy = a.y-b.y;
    float dz = a.z-b.z;
    return( sqrt(dx*dx+dy*dy+dz*dz) );
}


void drawSolidCube (float x,float y,float z,float a)
{
    a = a/2;

    // side  -X
    glBegin( GL_POLYGON );
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y-a, z+a);
        glVertex3f(x-a, y+a, z+a);
        glVertex3f(x-a, y+a, z-a);
    glEnd();

    // side +X
    glBegin( GL_POLYGON );
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(x+a, y-a, z-a);
        glVertex3f(x+a, y-a, z+a);
        glVertex3f(x+a, y+a, z+a);
        glVertex3f(x+a, y+a, z-a);
    glEnd();

    // side -Y
    glBegin( GL_POLYGON );
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y-a, z+a);
        glVertex3f(x+a, y-a, z+a);
        glVertex3f(x+a, y-a, z-a);
    glEnd();

    // side +Y
    glBegin( GL_POLYGON );
        glNormal3f(0.0, +1.0, 0.0);
        glVertex3f(x-a, y+a, z-a);
        glVertex3f(x-a, y+a, z+a);
        glVertex3f(x+a, y+a, z+a);
        glVertex3f(x+a, y+a, z-a);
    glEnd();

    // side -Z
    glBegin( GL_POLYGON );
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y+a, z-a);
        glVertex3f(x+a, y+a, z-a);
        glVertex3f(x+a, y-a, z-a);
    glEnd();

    // side +Z
    glBegin( GL_POLYGON );
        glNormal3f(0.0, 0.0, +1.0);
        glVertex3f(x-a, y-a, z+a);
        glVertex3f(x-a, y+a, z+a);
        glVertex3f(x+a, y+a, z+a);
        glVertex3f(x+a, y-a, z+a);
    glEnd();
}


void drawCircleXY( float x, float y, float z, float r )
{
    int n = 64;
    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    glBegin( GL_LINE_LOOP );
    for( int i=0; i<n; i++)
    {
        glVertex3f( x+r*cos(alpha), y+r*sin(alpha), z );
        alpha += dalpha;
    }
    glEnd();
}


void drawCone ( float x, float y, float z, float r, float h )
{
    int n = 32;

    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);

        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        // surface
        glBegin( GL_LINE_LOOP );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
            glVertex3f( x,     y,     z+h );
        glEnd();

        // bottom
        glBegin( GL_LINE_LOOP );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();
        alpha += dalpha;
    }
}

void drawCylinder ( float x, float y, float z, float r, float h )
{
    int n = 32;

    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);

        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        // surface
        glBegin( GL_LINE_LOOP );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
            glVertex3f( x+dx2, y+dy2, z+h );
            glVertex3f( x+dx1, y+dy1, z+h );
        glEnd();

        // bottom
        glBegin( GL_LINE_LOOP );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();

        // top
        glBegin( GL_LINE_LOOP );
            glVertex3f( x,     y,     z+h );
            glVertex3f( x+dx1, y+dy1, z+h );
            glVertex3f( x+dx2, y+dy2, z+h );
        glEnd();

        alpha += dalpha;
    }
}


void drawSolidCylinder ( float x, float y, float z, float r, float h, int n )
{


    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);

        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        // surface
        glBegin( GL_POLYGON );
            glNormal3f( cos(alpha+dalpha/2), sin(alpha+dalpha/2), 0 );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
            glVertex3f( x+dx2, y+dy2, z+h );
            glVertex3f( x+dx1, y+dy1, z+h );
        glEnd();

        // bottom
        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, -1 );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();

        // top
        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, 1 );
            glVertex3f( x,     y,     z+h );
            glVertex3f( x+dx1, y+dy1, z+h );
            glVertex3f( x+dx2, y+dy2, z+h );
        glEnd();

        alpha += dalpha;
    }
}


void drawSolidCone ( float x, float y, float z, float r, float h )
{
    int n = 32;

    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);

        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        float cosbeta = h/sqrt(h*h+r*r);
        float sinbeta = r/sqrt(h*h+r*r);
        float nx = cos(alpha+dalpha/2)*cosbeta;
        float ny = sin(alpha+dalpha/2)*cosbeta;
        float nz = sinbeta;

        // surface
        glBegin( GL_POLYGON );
            glNormal3f( nx, ny, nz );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
            glVertex3f( x,     y,     z+h );
        glEnd();

        // bottom
        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, -1 );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();
        alpha += dalpha;
    }
}


void drawSolidPrism( float x, float y, float z, float r, float h ,   int n  )
{    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);

        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        glBegin( GL_POLYGON );
            glNormal3f( cos(alpha+dalpha/2), sin(alpha+dalpha/2), 0 );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
            glVertex3f( x+dx2, y+dy2, z+h );
            glVertex3f( x+dx1, y+dy1, z+h );
        glEnd();

        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, -1 );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();

        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, 1 );
            glVertex3f( x,     y,     z+h );
            glVertex3f( x+dx1, y+dy1, z+h );
            glVertex3f( x+dx2, y+dy2, z+h );
        glEnd();
        alpha += dalpha;
    }
}

void drawWall (float x,float y,float z,float t, float l, float h)  // t for thickness, l for length, h for height
{


    // side  -X
    glBegin( GL_POLYGON );
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(x-l, y-t, z-h);
        glVertex3f(x-l, y-t, z+h);
        glVertex3f(x-l, y+t, z+h);
        glVertex3f(x-l, y+t, z-h);
    glEnd();

    // side +X
    glBegin( GL_POLYGON );
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(x+l, y-t, z-h);
        glVertex3f(x+l, y-t, z+h);
        glVertex3f(x+l, y+t, z+h);
        glVertex3f(x+l, y+t, z-h);
  glEnd();

    // side -Y
    glBegin( GL_POLYGON );
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(x-l, y-t, z-h);
        glVertex3f(x-l, y-t, z+h);
        glVertex3f(x+l, y-t, z+h);
        glVertex3f(x+l, y-t, z-h);
    glEnd();

    // side +Y
    glBegin( GL_POLYGON );
        glNormal3f(0.0, +1.0, 0.0);
        glVertex3f(x-l, y+t, z-h);
        glVertex3f(x-l, y+t, z+h);
        glVertex3f(x+l, y+t, z+h);
        glVertex3f(x+l, y+t, z-h);
    glEnd();

    // side -Z
    glBegin( GL_POLYGON );
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(x-l, y-t, z-h);
        glVertex3f(x-l, y+t, z-h);
        glVertex3f(x+l, y+t, z-h);
        glVertex3f(x+l, y-t, z-h);
    glEnd();

    // side +Z
    glBegin( GL_POLYGON );
        glNormal3f(0.0, 0.0, +1.0);
        glVertex3f(x-l, y-t, z+h);
        glVertex3f(x-l, y+t, z+h);
        glVertex3f(x+l, y+t, z+h);
        glVertex3f(x+l, y-t, z+h);
    glEnd();
}

void drawTruncatedCone( float x, float y, float z, float r, float r1, float h, int n )
{
float h1 = h - h*r1/r;
    float alpha = 0.0;
    float dalpha = 2*M_PI/n;
    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);
        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        float dx3 = r1*cos(alpha);
        float dy3 = r1*sin(alpha);
        float dx4 = r1*cos(alpha+dalpha);
        float dy4 = r1*sin(alpha+dalpha);

        float cosbeta = h/sqrt(h*h+r*r);
        float sinbeta = r/sqrt(h*h+r*r);
        float nx = cos(alpha+dalpha/2)*cosbeta;
        float ny = sin(alpha+dalpha/2)*cosbeta;
        float nz = sinbeta;
        // surface
        glBegin( GL_POLYGON );
            glNormal3f( nx, ny, nz );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
           glVertex3f( x+dx4, y+dy4, z+h1 );
           glVertex3f( x+dx3, y+dy3, z+h1 );
glEnd();

        // bottom
        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, -1 );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();

        //top
                glBegin( GL_POLYGON );
            glNormal3f( 0, 0, 1 );
            glVertex3f( x,     y,     z+h1 );
            glVertex3f( x+dx3, y+dy3, z+h1 );
            glVertex3f( x+dx4, y+dy4, z+h1 );
        glEnd();
        alpha += dalpha;
    }     }


void drawReverseTruncatedCone( float x, float y, float z, float r, float r1, float h )
{  int n = 32;
float h1 = h - h*r1/r;
    float alpha = 0.0;
    float dalpha = 2*M_PI/n;
    for( int i=0; i<n; i++)
    {
        float dx1 = r1*cos(alpha);
        float dy1 = r1*sin(alpha);
        float dx2 = r1*cos(alpha+dalpha);
        float dy2 = r1*sin(alpha+dalpha);

        float dx3 = r*cos(alpha);
        float dy3 = r*sin(alpha);
        float dx4 = r*cos(alpha+dalpha);
        float dy4 = r*sin(alpha+dalpha);

        float cosbeta = h/sqrt(h*h+r*r);
        float sinbeta = r/sqrt(h*h+r*r);
        float nx = cos(alpha+dalpha/2)*cosbeta;
        float ny = sin(alpha+dalpha/2)*cosbeta;
        float nz = sinbeta;
        // surface
        glBegin( GL_POLYGON );
            glNormal3f( nx, ny, nz );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
           glVertex3f( x+dx4, y+dy4, z+h1 );
           glVertex3f( x+dx3, y+dy3, z+h1 );
glEnd();

        // bottom
        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, -1 );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();

        //top
                glBegin( GL_POLYGON );
            glNormal3f( 0, 0, 1 );
            glVertex3f( x,     y,     z+h1 );
            glVertex3f( x+dx3, y+dy3, z+h1 );
            glVertex3f( x+dx4, y+dy4, z+h1 );
        glEnd();
        alpha += dalpha;
    }     }



void drawReverseTruncatedStripedCone( float x, float y, float z, float r, float r1, float h , COS397_COLOR c1, COS397_COLOR c2)
{  int n = 32;
float h1 = h - h*r1/r;
    float alpha = 0.0;
    float dalpha = 2*M_PI/n;
    bool flag = true;
    for( int i=0; i<n; i++)
    {
        float dx1 = r1*cos(alpha);
        float dy1 = r1*sin(alpha);
        float dx2 = r1*cos(alpha+dalpha);
        float dy2 = r1*sin(alpha+dalpha);

        float dx3 = r*cos(alpha);
        float dy3 = r*sin(alpha);
        float dx4 = r*cos(alpha+dalpha);
        float dy4 = r*sin(alpha+dalpha);

        float cosbeta = h/sqrt(h*h+r*r);
        float sinbeta = r/sqrt(h*h+r*r);
        float nx = cos(alpha+dalpha/2)*cosbeta;
        float ny = sin(alpha+dalpha/2)*cosbeta;
        float nz = sinbeta;
        // surface
        if (i%4 ==0 ) flag = !flag;

        if (!flag) glColor3f(c1.red,c1.green,c1.blue);
        else glColor3f(c2.red,c2.green,c2.blue);
        glBegin( GL_POLYGON );
            glNormal3f( nx, ny, nz );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
           glVertex3f( x+dx4, y+dy4, z+h1 );
           glVertex3f( x+dx3, y+dy3, z+h1 );
glEnd();

        // bottom
        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, -1 );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();

        //top
                glBegin( GL_POLYGON );
            glNormal3f( 0, 0, 1 );
            glVertex3f( x,     y,     z+h1 );
            glVertex3f( x+dx3, y+dy3, z+h1 );
            glVertex3f( x+dx4, y+dy4, z+h1 );
        glEnd();
        alpha += dalpha;
    }     }

COS397_POINT spherical( float alpha, float beta, float r )
{
    COS397_POINT p;
    p.x = r*cos(alpha)*cos(beta);
    p.y = r*sin(alpha)*cos(beta);
    p.z = r*sin(beta);
    return p;
}


void drawSphere( float x, float y, float z, float r )
{  int na=32;
    int nb=32;
    float alpha;
    float dalpha = 2.0*M_PI/na;
    float beta;
    float dbeta = 1.0*M_PI/nb;

    beta = M_PI/2;
    for( int j=0; j<nb; j++, beta-=dbeta)
    {
        alpha = 0;
        for( int i=0; i<na; i++, alpha+=dalpha)
        {
            glBegin( GL_LINE_LOOP );

            COS397_POINT a = spherical(alpha,beta,r);
            COS397_POINT b = spherical(alpha+dalpha,beta,r);
            COS397_POINT c = spherical(alpha+dalpha,beta-dbeta,r);
            COS397_POINT d = spherical(alpha,beta-dbeta,r);

            glVertex3f(x+a.x,y+a.y,z+a.z);
            glVertex3f(x+b.x,y+b.y,z+b.z);
            glVertex3f(x+c.x,y+c.y,z+c.z);
            glVertex3f(x+d.x,y+d.y,z+d.z);
            glEnd( );
        }
    }
}


void drawSolidSphere( float x, float y, float z, float r )
{ int na=32;
    int nb=32;
    float alpha;
    float dalpha = 2.0*M_PI/na;
    float beta;
    float dbeta = 1.0*M_PI/nb;

    beta = M_PI/2;
    for( int j=0; j<nb; j++, beta-=dbeta)
    {
        alpha = 0;
        for( int i=0; i<na; i++, alpha+=dalpha)
        {
            glBegin( GL_POLYGON );

            COS397_POINT a = spherical(alpha,beta,r);
            COS397_POINT b = spherical(alpha+dalpha,beta,r);
            COS397_POINT c = spherical(alpha+dalpha,beta-dbeta,r);
            COS397_POINT d = spherical(alpha,beta-dbeta,r);

            COS397_POINT n = spherical(alpha+dalpha/2,beta-dbeta/2,0.8);
            glNormal3f(n.x,n.y,n.z);

            glVertex3f(x+a.x,y+a.y,z+a.z);
            glVertex3f(x+b.x,y+b.y,z+b.z);
            glVertex3f(x+c.x,y+c.y,z+c.z);
            glVertex3f(x+d.x,y+d.y,z+d.z);
            glEnd( );
        }
    }
}


void drawSmoothSphere( float x, float y, float z, float r )
{ int na=32;
    int nb=32;
    float alpha;
    float dalpha = 2.0*M_PI/na;
    float beta;
    float dbeta = 1.0*M_PI/nb;

    beta = M_PI/2;
    for( int j=0; j<nb; j++, beta-=dbeta)
    {
        alpha = 0;
        for( int i=0; i<na; i++, alpha+=dalpha)
        {
            COS397_POINT p;
            glBegin( GL_POLYGON );

            p = spherical(alpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+r*p.x,y+r*p.y,z+r*p.z);

            p = spherical(alpha+dalpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+r*p.x,y+r*p.y,z+r*p.z);

            p = spherical(alpha+dalpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+r*p.x,y+r*p.y,z+r*p.z);

            p = spherical(alpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+r*p.x,y+r*p.y,z+r*p.z);

            glEnd( );
        }
    }
}

void drawSmoothEllipsoid( float x, float y, float z, float rx, float ry, float rz )
{ int na=32;
    int nb=32;
    float alpha;
    float dalpha = 2.0*M_PI/na;
    float beta;
    float dbeta = 1.0*M_PI/nb;

    beta = M_PI/2;
    for( int j=0; j<nb; j++, beta-=dbeta)
    {
        alpha = 0;
        for( int i=0; i<na; i++, alpha+=dalpha)
        {
            COS397_POINT p;
            glBegin( GL_POLYGON );

            p = spherical(alpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha+dalpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha+dalpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            glEnd( );
        }
    }
}

void drawSmoothEllipsoidPatch(
        float x, float y, float z,     // center coordinates
        float rx, float ry, float rz,  // radius
        float a1, float a2,            // horizontal angle range
        float b1, float b2             // vertical angle range
    )
{ int na=32;
    int nb=32;
    float alpha;
    float dalpha = (a2-a1)/(float)na;
    float beta;
    float dbeta = (b2-b1)/(float)nb;

    beta = b2;
    for( int j=0; j<nb; j++, beta-=dbeta)
    {
        alpha = a1;
        for( int i=0; i<na; i++, alpha+=dalpha)
        {
            COS397_POINT p;
            glBegin( GL_POLYGON );

            p = spherical(alpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha+dalpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha+dalpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            glEnd( );
        }
    }
}



COS397_POINT vector_sum( COS397_POINT v1, COS397_POINT v2)
{

    COS397_POINT p;
    p.x= v1.x+v2.x;
    p.y= v1.y+v2.y;
    p.z= v1.z+v2.z;
    return p;
}

COS397_POINT vector_diff( COS397_POINT v1, COS397_POINT v2)
{

    COS397_POINT p;
    p.x= -v1.x+v2.x;
    p.y= -v1.y+v2.y;
    p.z= -v1.z+v2.z;
    return p;
}

COS397_POINT vector_scalar( COS397_POINT v1, float a)
{
    COS397_POINT p;
    p.x= v1.x*a;
    p.y= v1.y*a;
    p.z= v1.z*a;
    return p;
}

COS397_POINT unit_vector( COS397_POINT v1)
{
    float len = sqrt (v1.x*v1.x + v1.y*v1.y +v1.z*v1.z);
    COS397_POINT p;
    p.x= v1.x/len;
    p.y= v1.y/len;
    p.z= v1.z/len;
    return p;
}
COS397_POINT vector_product( COS397_POINT v1, COS397_POINT v2)
{

    COS397_POINT p,uv1,uv2;
    uv1 = unit_vector(v1);
    uv2 = unit_vector(v2);
    p.x= uv1.y*uv2.z -uv1.z*uv2.y;
    p.y= uv1.z*uv2.x -uv1.x*uv2.z;
    p.z= uv1.x*uv2.y -uv1.y*uv2.x;
    return p;
}

COS397_POINT mid_point( COS397_POINT v1, COS397_POINT v2)
{
    COS397_POINT p;
    p.x= (v2.x+v1.x)/2;
    p.y= (v2.y+v1.y)/2;
    p.z= (v2.z+v1.z)/2;
    return p;
}

COS397_POINT BSpline(COS397_POINT p0, COS397_POINT p1, COS397_POINT p2, COS397_POINT p3, float t)
{


    float a0 = (0- t*t*t+3*t*t -3*t+1)/6;
    float a1 = (3*t*t*t-6*t*t+4)/6;
    float a2 =(0-3*t*t*t+3*t*t+3*t+1)/6;
    float a3 =(t*t*t)/6;
    return  vector_sum( vector_sum(vector_scalar(p0,a0) , vector_scalar(p1,a1)),
                        vector_sum(vector_scalar(p2,a2),vector_scalar(p3,a3)));

}

float scalar_product( COS397_POINT v1, COS397_POINT v2)
{

    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;

}

void drawSolidHollowCylinder ( float x, float y, float z, float r, float h )
{
    int n = 24;

    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);

        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        // surface
        glBegin( GL_POLYGON );
            glNormal3f( cos(alpha+dalpha/2), sin(alpha+dalpha/2), 0 );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
            glVertex3f( x+dx2, y+dy2, z+h );
            glVertex3f( x+dx1, y+dy1, z+h );
        glEnd();

        alpha += dalpha;
    }
}

void drawSlopedSolidHollowCylinder ( COS397_POINT p_start, COS397_POINT p_end, float r )
{
            float dist= distance(p_start,p_end);
            COS397_POINT  vectz = {0,0,1};
            COS397_POINT  vectp = vector_diff(p_start,p_end);
            COS397_POINT rot_vect = vector_product(vectz, vectp);
            float  angle = 180 / M_PI * acos (scalar_product(vectz, vectp) / dist);
            glPushMatrix();
            glTranslatef(p_start.x ,p_start.y ,p_start.z);
            glRotatef(angle,rot_vect.x,rot_vect.y,rot_vect.z);
            drawSolidHollowCylinder (0 ,0 ,0,r,dist  );
           glPopMatrix();}
void drawSlopedSmoothEllipsoid ( COS397_POINT p_start, COS397_POINT p_end, float rx,float ry )
{
            float dist= distance(p_start,p_end);
            COS397_POINT  vectz = {0,0,1};
            COS397_POINT midp = mid_point(p_start,p_end);
            COS397_POINT  vectp = vector_diff(p_start,p_end);
            COS397_POINT rot_vect = vector_product(vectz, vectp);
            float  angle = 180 / M_PI * acos (scalar_product(vectz, vectp) / dist);
            glPushMatrix();
            glTranslatef(midp.x ,midp.y ,midp.z);
            glRotatef(angle,rot_vect.x,rot_vect.y,rot_vect.z);
            drawSmoothEllipsoid (0 ,0 ,0,rx,ry,dist/2 );
           glPopMatrix();
}

void drawTextureEllipsoidPatch(
        float x, float y, float z,     // center
        float rx, float ry, float rz,  // ellipsoid radius
        float a1, float a2,            // horizontal angle
        float b1, float b2             // vertical angle
    )
{
   int na = 16*2;
    int nb = 16*2;


    float alpha;
    float dalpha = (a2-a1)/na;
    float beta;
    float dbeta = (b2-b1)/nb;


    beta = b2;
    for( int j=0; j<nb; j++, beta-=dbeta)
    {
        alpha = a1;
        for( int i=0; i<na; i++, alpha+=dalpha)
        {
            COS397_POINT p;
            glBegin( GL_POLYGON );

            p = spherical(alpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glTexCoord2f(alpha,beta);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha+dalpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
             glTexCoord2f(alpha+dalpha,beta);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha+dalpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
              glTexCoord2f( alpha+dalpha,beta-dbeta);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
               glTexCoord2f( alpha,beta-dbeta);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            glEnd( );
        }
    }
}


