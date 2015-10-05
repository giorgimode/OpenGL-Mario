#ifndef COS397LIB_H_INCLUDED
#define COS397LIB_H_INCLUDED

struct COS397_COLOR
{
    float red;
    float green;
    float blue;
} ;
struct COS397_POINT
{
    float x;
    float y;
    float z;
} ;


bool running();
void init();
void finit();
float random(float a, float b);

void drawCube( float x, float y, float z, float a );
void drawOxyz();

COS397_POINT point( float x, float y, float z );
float distance( COS397_POINT a, COS397_POINT b );
void drawSolidCube (float x,float y,float z,float a);

void drawCircleXY( float x, float y, float z, float r );
void drawCone ( float x, float y, float z, float r, float h );

void drawCylinder ( float x, float y, float z, float r, float h );
void drawSolidCylinder ( float x, float y, float z, float r, float h, int n );

void drawSolidCone ( float x, float y, float z, float r, float h );

void drawSolidPrism( float x, float y, float z, float r, float h ,   int n  );
void drawTruncatedCone( float x, float y, float z, float r, float r1, float h, int n );

void drawReverseTruncatedCone( float x, float y, float z, float r, float r1, float h );
void drawReverseTruncatedStripedCone( float x, float y, float z, float r, float r1, float h,COS397_COLOR c1, COS397_COLOR c2 );


COS397_POINT spherical( float alpha, float beta, float r );
void drawSphere( float x, float y, float z, float r );
void drawSolidSphere( float x, float y, float z, float r );
void drawSmoothSphere( float x, float y, float z, float r );
void drawSmoothEllipsoid( float x, float y, float z, float rx, float ry, float rz );
void drawSmoothEllipsoidPatch(
        float x, float y, float z,     // center coordinates
        float rx, float ry, float rz,  // radius
        float a1, float a2,            // horizontal angle range
        float b1, float b2             // vertical angle range
    );

void drawWall (float x,float y,float z,float t, float l, float h);

COS397_POINT vector_sum( COS397_POINT v1, COS397_POINT v2);

COS397_POINT vector_diff( COS397_POINT v1, COS397_POINT v2);

COS397_POINT vector_scalar( COS397_POINT v1, float a);

COS397_POINT unit_vector( COS397_POINT v1);

COS397_POINT vector_product( COS397_POINT v1, COS397_POINT v2);

COS397_POINT mid_point( COS397_POINT v1, COS397_POINT v2);

COS397_POINT BSpline(COS397_POINT p0, COS397_POINT p1, COS397_POINT p2, COS397_POINT p3, float t);

void drawSolidHollowCylinder ( float x, float y, float z, float r, float h );

void drawSlopedSolidHollowCylinder ( COS397_POINT p_start, COS397_POINT p_end, float r );
void drawSlopedSmoothEllipsoid ( COS397_POINT p_start, COS397_POINT p_end, float rx,float ry );

void drawTextureEllipsoidPatch(
        float x, float y, float z,     // center
        float rx, float ry, float rz,  // ellipsoid radius
        float a1, float a2,            // horizontal angle
        float b1, float b2             // vertical angle
    );

#endif // COS397LIB_H_INCLUDED
