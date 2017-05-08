#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include<iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <iostream>
using namespace std;

const static int m=35;
const static int n=35;
const double PI = 3.14;
float Y = -6,r=10;   // Y of ground - reduis
GLfloat z=0,d1 = 0 ,d2 = 0 ; //change of movement in camera
const static int numberBall = ((int)m/6)-2;       //number of ball
float X_Ball1 , Y_Ball1   ,  X_Ball2 , Y_Ball2  ;
float timer1 = 1.5 ,  timer2 = 1;
float v2=0.01 ,v1=0.01; //velocity
bool TURN_Ball_2 = false;
int Turn_Back_Ball_2 = 0, Turn_Back_Ball_1 = 1;




GLdouble mnor[4] = { 0.0, 0.0, 1.0, 0.0 };

//0:emerald     1:jade  2:obsidian  3:pearl 4:ruby  5:turquoise 6:brass     7:bronze       8:chrome     9:copper    10:gold     11:silver   12:Plastic(Black)   13:Plastic(Cyan)

GLfloat Ambient[13][4] ={
   0.0215,  0.1745,   0.0215,  1.0,
   0.135,     0.2225,   0.1575,   1.0,
  0.05375, 0.05,    0.06625, 1.0,
   0.25,     0.20725,  0.20725,  1.0,
    0.1745,   0.01175,  0.01175,   1.0,
    0.1,     0.18725, 0.1745,  1.0,
    0.329412,  0.223529, 0.027451, 1.0,
    0.2125,   0.1275,   0.054,   1.0,
    0.25,    0.25,     0.25,     1.0,
    0.19125,  0.0735,   0.0225,  1.0,
    0.24725,  0.1995,   0.0745,    1.0,
    0.19225,  0.19225,  0.19225, 1.0,
   // 0.0,    0.0,    0.0,  1.0,
    0.0,   0.1,    0.06,    1.0,
};

GLfloat Diffuse [13][4] ={
0.07568, 0.61424,  0.07568, 1.0,
    0.54,      0.89,     0.63,     1.0,
    0.18275, 0.17,    0.22525, 1.0,
1,        0.829,    0.829,    1.0,
    0.61424,  0.04136,  0.04136,   1.0,
    0.396,   0.74151, 0.69102, 1.0,
    0.780392,  0.568627, 0.113725, 1.0,
    0.714,    0.4284,   0.18144, 1.0,
    0.4,     0.4,      0.4,      1.0,
    0.7038,   0.27048,  0.0828,  1.0,
    0.75164,  0.60648,  0.22648,   1.0,
 //   0.50754,  0.50754,  0.50754, 1.0,
    0.01,   0.01,   0.01, 1.0,
0.0,   0.50980392,0.50980392,1.0,
};
GLfloat Specular[13][4] ={
    
    0.633,   0.727811, 0.633,   1.0,
    0.316228,  0.316228, 0.316228, 1.0,
    0.332741,0.328634,0.346435,1.0,
    0.296648, 0.296648, 0.296648, 1.0,
    0.727811, 0.626959, 0.626959,  1.0,
    0.297254,0.30829, 0.306678,1.0,
    0.992157,  0.941176, 0.807843, 1.0,
    0.393548, 0.271906, 0.166721,1.0,
    0.774597,0.774597, 0.774597, 1.0,
    0.256777, 0.137622, 0.086014,1.0,
    0.628281, 0.555802, 0.366065,  1.0,
    0.508273, 0.508273, 0.508273,1.0,
 //   0.50,   0.50,   0.50, 1.0,
    0.50196078,0.50196078,0.50196078,1.0,

};
GLfloat Shininess[13][1] = {
    76.8,
    12.8,
    38.4,
    10.24,
    76.8,
    12.8,
    27.89743616,
    25.6,
    76.8,
    12.8,
    51.2,
    51.2,
    32,
};

float Vertex[m*n][8] = {
    
};

void initVertex(){
    int counter=0;
    while(counter<m*n){
        for( int j=0; j< n ; j++){
            for(int i =0 ; i< m ; i++){
                Vertex[counter][0]=i;
                Vertex[counter][1]=j;
                Vertex[counter][2]=i+1;
                Vertex[counter][3]=j;
                Vertex[counter][4]=i+1;
                Vertex[counter][5]=j+1;
                Vertex[counter][6]=i;
                Vertex[counter][7]=j+1;
                counter++;
            
            }
        }
    }
}

void ground(){
   
    glDisable(GL_LIGHTING);
    for(int i =0 ; i< m*n; i++){
        glPushMatrix();
        glBegin(GL_QUADS);
        if(i%2==0)
            glColor3f(1,1,1);   //white
        else
            glColor3f(0.5,0.5,0.5);
        
        glVertex3f( Vertex[i][0], Y, Vertex[i][1]);
        glVertex3f( Vertex[i][2], Y, Vertex[i][3]);
        glVertex3f( Vertex[i][4], Y, Vertex[i][5]);
        glVertex3f( Vertex[i][6], Y, Vertex[i][7]);
        glEnd();
        glPopMatrix();

    }
    glEnable(GL_LIGHTING);
}
void drawBall(){
    glutSolidSphere(2, 32, 32);
}
void drawline(float X_start,float Y_start , float X_end, float Y_end){
    glDisable(GL_LIGHTING);
    glPushMatrix();
   
    glColor3f( 1,1,1 );
    glBegin(GL_LINES);
    glVertex3f(X_start, Y_start, 0.0);
    glVertex3f(X_end, Y_end, 0.0);
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
}
void paye(){
    glDisable(GL_LIGHTING);
    //1
    glPushMatrix();
    glColor3f( 0.24,0.14,0.05 );
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-3, r, -1.0);
    glVertex3f(4*numberBall , r, -1.0);
    glVertex3f(-3, r, 1.0);
    glVertex3f(4*numberBall , r, 1.0);
    glEnd();
    glPopMatrix();
    //2
    glPushMatrix();
    glColor3f( 0.24,0.14,0.05 );
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-3, r+1, -1.0);
    glVertex3f(4*numberBall , r+1, -1.0);
    glVertex3f(-3, r+1, 1.0);
    glVertex3f(4*numberBall , r+1, 1.0);
    glEnd();
    glPopMatrix();
    //3
    glPushMatrix();
    glColor3f( 0.24,0.14,0.05 );
    glBegin(GL_QUAD_STRIP);
    glVertex3f(4*numberBall , r, -1.0);
    glVertex3f(4*numberBall , r+1, -1.0);
    glVertex3f(4*numberBall , r, 1.0);
    glVertex3f(4*numberBall , r+1, 1.0);
    glEnd();
    glPopMatrix();
    //4
    glPushMatrix();
    glColor3f( 0.24,0.14,0.05 );
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-3, r+1, 1.0);
    glVertex3f(-3, r, 1.0);
    glVertex3f(-3, r+1, -1.0);
    glVertex3f(-3, r, -1.0);
    glEnd();
    glPopMatrix();
    //5
    glPushMatrix();
    glColor3f( 0.24,0.14,0.05 );
    glBegin(GL_QUADS);
    glVertex3f(4*numberBall , r, 1.0);
    glVertex3f(4*numberBall , r+1, 1.0);
    glVertex3f(-3, r+1, 1.0);
    glVertex3f(-3, r, 1.0);
    glEnd();
    glPopMatrix();
    //6
    glPushMatrix();
    glColor3f( 0.24,0.14,0.05 );
    glBegin(GL_QUADS);
    glVertex3f(4*numberBall , r, -1.0);
    glVertex3f(4*numberBall , r+1, -1.0);
    glVertex3f(-3, r+1, -1.0);
    glVertex3f(-3, r,-1.0);
    glEnd();
    glPopMatrix();
    //PAYE KENARI 1
    //1
    glPushMatrix();
    glColor3f( 0.24,0.14,0.05 );
    glBegin(GL_QUADS);
    glVertex3f(-3, r+1, -1.0);
    glVertex3f(-3, r+1, 1.0);
    glVertex3f(-(m-(4*numberBall))/2 -2, Y-2, 1.0);
    glVertex3f(-(m-(4*numberBall))/2 -2, Y-2, -1.0);
    glEnd();
    glPopMatrix();
    //2
    glPushMatrix();
    glColor3f( 0.24,0.14,0.05 );
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-3, r+1, -1.0);
    glVertex3f(-3, r, -1.0);
    glVertex3f(-(m-(4*numberBall))/2 -2, Y-2, -1.0);
    glVertex3f(-(m-(4*numberBall))/2 -1, Y-2, -1.0);
    glEnd();
    glPopMatrix();
    //3
    glPushMatrix();
    glColor3f( 0.24,0.14,0.05 );
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-3, r+1, 1.0);
    glVertex3f(-3, r, 1.0);
    glVertex3f(-(m-(4*numberBall))/2 -2, Y-2, 1.0);
    glVertex3f(-(m-(4*numberBall))/2 -1, Y-2, 1.0);
    glEnd();
    glPopMatrix();
    
    //PAYE KENARI 2
    //1
    glPushMatrix();
    glColor3f( 0.24,0.14,0.05 );
    glBegin(GL_QUADS);
    glVertex3f(4*numberBall, r+1, -1.0);
    glVertex3f(4*numberBall, r+1, 1.0);
    glVertex3f(4*numberBall+(m-(4*numberBall))/2-1, Y-2, 1.0);
    glVertex3f(4*numberBall+(m-(4*numberBall))/2-1, Y-2, -1.0);
    glEnd();
    glPopMatrix();
    //2
    glPushMatrix();
    glColor3f( 0.24,0.14,0.05 );
    glBegin(GL_QUADS);
    glVertex3f(4*numberBall, r+1, -1.0);
    glVertex3f(4*numberBall, r, -1.0);
    glVertex3f(4*numberBall+(m-(4*numberBall))/2-2, Y-2, -1.0);
    glVertex3f(4*numberBall+(m-(4*numberBall))/2-1, Y-2, -1.0);
    glEnd();
    glPopMatrix();
    //3
    glPushMatrix();
    glColor3f( 0.24,0.14,0.05 );
    glBegin(GL_QUADS);
    glVertex3f(4*numberBall, r+1, 1.0);
    glVertex3f(4*numberBall, r, 1.0);
    glVertex3f(4*numberBall+(m-(4*numberBall))/2-2, Y-2, 1.0);
    glVertex3f(4*numberBall+(m-(4*numberBall))/2-1, Y-2, 1.0);
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
}
void drawBalls(){
    glDisable(GL_LIGHTING);
   glTranslated((m-(4*numberBall))/2 + 2, Y+n/10, n/2);
    
    paye();
    
    for( int i =0 ; i< numberBall ; i++){
        glPushMatrix();
      if (i == numberBall - 1) {
           if (TURN_Ball_2 == true) {
               if (Turn_Back_Ball_2 == 0) { timer1 += v2; v2+=0.0001; }
                else  {timer1 -= v2;  v2-=0.0001;}
               
                if (timer1 > 1.6) {Turn_Back_Ball_2 = 1;  v2=0.01; TURN_Ball_2 = false;}
                if (timer1 < 1) {   Turn_Back_Ball_2 = 0;   v2=0.01;}

                X_Ball2 = r*cos(-timer1);
                Y_Ball2 = r + r*sin(-timer1);
                
                glPushMatrix();
                glTranslatef(3*i, 0, 0);
                 drawline(i, r, X_Ball2+i, Y_Ball2);
                glPopMatrix();
                glTranslatef(X_Ball2, Y_Ball2, 0);
            }
            else {
                glPushMatrix();
                glTranslatef(3*i, 0, 0);
                drawline(i, r, i, 0);
               glPopMatrix();
            }
        }
        else if (i == 0) {
            if (TURN_Ball_2 == false) {
                if (Turn_Back_Ball_1 == 0)  { timer2 += v1; v1+=0.0001;}
                else{   timer2 -= v1;   v1-=0.0001;}
                if (timer2 > 1.6) { Turn_Back_Ball_1 = 1; v1=0.01; TURN_Ball_2 = true;  }
                if (timer2 < 1) { Turn_Back_Ball_1 = 0; v1=0.01;}
                
                X_Ball1 = -r*cos(-timer2);
                Y_Ball1= r + r*sin(-timer2);
               
                glPushMatrix();
                drawline(i, r, X_Ball1, Y_Ball1);
                glPopMatrix();
                glTranslatef(X_Ball1, Y_Ball1, 0);
               
           }
           else {
                glPushMatrix();
                glTranslatef(3*i, 0, 0);
                drawline(i, r, i, 0);
                glPopMatrix();
            }
        }
        else {
   
        glPushMatrix();
            glTranslatef(3*i, 0, 0);
              drawline(i, r, i, 0);
        glPopMatrix();
            
      }
         glTranslatef(4*i, 0, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT,  Ambient[i]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,  Diffuse[i]);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  Specular[i]);
        glMaterialfv(GL_FRONT, GL_SHININESS,  Shininess[i]);
        drawBall();
        glPopMatrix();
        
    }
  }
void objs( )
{
    glPushMatrix();
    ground();
    glPopMatrix();
    glPushMatrix();
    drawBalls();
    glPopMatrix();
}



void display( )
{

    GLint buffers = GL_NONE;
    
    glPushMatrix();
    glTranslatef(0,0,z);
    glGetIntegerv( GL_DRAW_BUFFER, &buffers );
    glTranslated(m / 2, Y + 3, 0);
    glRotatef( d1, 0, 1, 0);
    glTranslated(-m / 2, -Y - 3, 0);
    glRotatef(d2, 1, 0, 0);
  
    
    glClearStencil( 0x0 );
    glClear( GL_STENCIL_BUFFER_BIT );
    glStencilFunc(GL_ALWAYS, 0x1, 0x1 );
    glStencilOp( GL_REPLACE, GL_REPLACE, GL_REPLACE );
    glDrawBuffer( GL_NONE );
    glEnable( GL_STENCIL_TEST );
    
    glBegin( GL_QUADS );
    glVertex3f( 0 , Y , 0 );
    glVertex3f( m , Y , 0 );
    glVertex3f( m , Y+n/3 , 0 );
    glVertex3f( 0 , Y+n/3, 0 );
    glEnd();
    
    glDrawBuffer( (GLenum) buffers );
    glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
    
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glPushMatrix();
    glScalef( 1 , 1 , -1 );
    
    if( (cos( d1 * PI / 180.0 ) < 0.0)  || (cos( d1 * PI / 180.0 ) < 0.0 ) )
    {
        mnor[2] = -1.0;
    }
    else
    {
        mnor[2] = 1.0;
    }

    glClipPlane( GL_CLIP_PLANE0 , mnor );
    glEnable( GL_CLIP_PLANE0 );
    
    glStencilFunc( GL_EQUAL , 0x1 , 0x1 );
    
    // draw real objects
    objs();
    
    glDisable( GL_CLIP_PLANE0 );
    glPopMatrix( );
    
    glDisable( GL_STENCIL_TEST );
    glDrawBuffer( GL_NONE );
    
    // draw the mirror pane into depth buffer -
    // to prevent object behind mirror from being render
    glBegin( GL_QUADS );
    glVertex3f( 0 , Y , 0 );
    glVertex3f( m , Y , 0 );
    glVertex3f( m , Y+n/3 , 0 );
    glVertex3f( 0 , Y+n/3, 0 );
    glEnd();
    
    // enable drawing to the color buffer
    glDrawBuffer( (GLenum) buffers );
    
    // draw Objects in the mirror
    glPushMatrix( );
    objs();
    glPopMatrix( );
    
    // mirror shine
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_BLEND );
    glDepthMask( GL_FALSE );
    glDepthFunc( GL_LEQUAL );
    glDisable( GL_LIGHTING );
    
    
    
    //JIVE
    glColor4f( 1 , 1 , 1 , 0.1 );
    glTranslatef( 0.0f, 0.0f, 0.001f * mnor[2] );
    glBegin( GL_QUADS );
    glVertex3f( 0 , Y , 0 );
    glVertex3f( m , Y , 0 );
    glVertex3f( m , Y+n/3 , 0 );
    glVertex3f( 0 , Y+n/3, 0 );
    glEnd( );
    
    glDisable( GL_BLEND );
    glDepthMask( GL_TRUE );
    glDepthFunc( GL_LESS );
    glEnable( GL_LIGHTING );
    
    glPopMatrix( );
    
    glFlush( );
    glutSwapBuffers( );
}

void init()
{
    if(m == 81) Y=-6;
    else Y=-2;
     initVertex();
    glClearColor( 0 , 0 , 0 , 1 );
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glFrontFace( GL_CCW );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glLineWidth(3 );
    
    GLfloat light_position[] = { 5,5,5, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}


void reshape( GLsizei w, GLsizei h )
{
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective( 45.0, (GLfloat) w / (GLfloat) h, 1.0, 300.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    gluLookAt(m/2, ((Y+n/2)/2)-6, m/2+n, m/2, ((Y+n/2)/2)-6, 0, 0, 1, 0);
}
void pressSpecialKey(int key, int xx, int yy)
{
    switch (key) {
        case 27:
            exit(1);
            break;
        case GLUT_KEY_UP: z++;break;
        case GLUT_KEY_DOWN : z-- ; break;
        case GLUT_KEY_RIGHT : d1-=2; break;
        case GLUT_KEY_LEFT : d1 +=2; break;
        case 'w':d2++;break;
        case 's' : d2--;break;
        default:
            break;
    }
}
int main( int argc, char ** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL );
    glutInitWindowSize( 1350, 800 );
    glutInitWindowPosition( 0, 0 );
    glutCreateWindow( "Mirror" );
    
    init();
    
    glutIdleFunc( display );
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutSpecialFunc(pressSpecialKey);
    glutMainLoop();
    return 0;
}