#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"
#define PI 3.1416

using namespace std;

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1000, windowWidth=1200;
GLfloat axis_x=0.0, axis_y=0.0;
float alpha,bita,theta;
GLboolean bRotate = false, uRotate = false;
unsigned int ID[50];
GLfloat eye[3]= {0,2,20};
GLfloat look[3]= {0,0,0};
GLfloat up[3]= {0,1,0};
GLboolean birds = false;
#include "Birdseye.h"

static GLfloat v_box[8][3] =
{
    {-2.0, 0.0, 0.0},
    {2.0, 0.0, 0.0},
    {-2.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},

    {-2.0, 2.0, 0.0},
    {2.0, 2.0, 0.0},
    {-2.0, 2.0, 2.0},
    {2.0, 2.0, 2.0}
};

static GLubyte quadIndices[6][4] =
{
    {0,2,3,1},
    {0,2,6,4},
    {2,3,7,6},
    {1,3,7,5},
    {1,5,4,0},
    {6,7,5,4}
};

static GLfloat v_box1[6][3] =
{
    {0.0, 0.0, 0.0},
    {2.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},

    {0.0, 2.0, 0.0},
    {2.0, 2.0, 0.0},
    {0.0, 2.0, 2.0},
};

static GLubyte quadIndices1[3][4] =
{
    {1,4,5,2},
    {0,2,5,3},
    {0,3,4,1},

};

static GLubyte quadIndices2[2][3] =
{
    {3,5,4},
    {0,1,2},

};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void reflect(float r, float g, float b, float shiny)
{
        GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat mat_ambient[] = { r, g, b, 1.0 };
        GLfloat mat_diffuse[] = { r,g,b, 1.0 };
        GLfloat mat_specular[] = { r,g,b, 1.0 };
        GLfloat mat_shininess[] = {shiny};

        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
}

void drawBox()
{
  //  glColor3f(1,1,1);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_box[quadIndices[i][0]][0], v_box[quadIndices[i][0]][1], v_box[quadIndices[i][0]][2],
                    v_box[quadIndices[i][1]][0], v_box[quadIndices[i][1]][1], v_box[quadIndices[i][1]][2],
                    v_box[quadIndices[i][2]][0], v_box[quadIndices[i][2]][1], v_box[quadIndices[i][2]][2]);

        glVertex3fv(&v_box[quadIndices[i][0]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_box[quadIndices[i][1]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v_box[quadIndices[i][2]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_box[quadIndices[i][3]][0]);glTexCoord2f(1,0);
    }
    glEnd();
    //glutSolidSphere (3.0, 20, 16);

}

void drawtri()
{
  //  glColor3f(1,1,1);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <3; i++)
    {
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_box1[quadIndices1[i][0]][0], v_box1[quadIndices1[i][0]][1], v_box1[quadIndices1[i][0]][2],
                    v_box1[quadIndices1[i][1]][0], v_box1[quadIndices1[i][1]][1], v_box1[quadIndices1[i][1]][2],
                    v_box1[quadIndices1[i][2]][0], v_box1[quadIndices1[i][2]][1], v_box1[quadIndices1[i][2]][2]);


        glVertex3fv(&v_box1[quadIndices1[i][0]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_box1[quadIndices1[i][1]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v_box1[quadIndices1[i][2]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_box1[quadIndices1[i][3]][0]);glTexCoord2f(1,0);

    }
    glEnd();
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <2; i++)
    {
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_box1[quadIndices2[i][0]][0], v_box1[quadIndices2[i][0]][1], v_box1[quadIndices2[i][0]][2],
                    v_box1[quadIndices2[i][1]][0], v_box1[quadIndices2[i][1]][1], v_box1[quadIndices2[i][1]][2],
                    v_box1[quadIndices2[i][2]][0], v_box1[quadIndices2[i][2]][1], v_box1[quadIndices2[i][2]][2]);


        glVertex3fv(&v_box1[quadIndices2[i][0]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_box1[quadIndices2[i][1]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v_box1[quadIndices2[i][2]][0]);glTexCoord2f(1,1);
        //glVertex3fv(&v_box1[quadIndices2[i][3]][0]);glTexCoord2f(1,0);

    }
    glEnd();
    //glutSolidSphere (3.0, 20, 16);

}




void light()
{
    //GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 10.0, 50.0, 1.0 };

    glEnable( GL_LIGHT0);

    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    /*GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);*/
}
void LoadTexture(const char*filename,int a);
void dustbin()
{
        glBindTexture(GL_TEXTURE_2D,ID[1]);
        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        //glColor4f(0.22f,0.25f,0.40f, 1.0f);
        reflect(.7, .7,.7, 60);

        glTranslatef(2,0.0,2.4);
        glScalef(10.0,2,10.0);
        glRotatef(-90, 1, 0, 0);

        GLUquadricObj *quadratic;
        quadratic = gluNewQuadric();
        gluQuadricOrientation(quadratic, GLU_OUTSIDE);
        gluQuadricNormals(quadratic, true);
        gluQuadricTexture(quadratic, true);

        gluCylinder(quadratic,0.15f,0.1f,1.0f,32,32);
        glTranslatef(0,0,1);
        gluCylinder(quadratic,0.1f,0.12f,0.7f,32,32);
        glPushMatrix();
        glTranslatef(0,0,0.7);
        gluDisk(quadratic,0.09,.12,32,32);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,ID[6]);
        glEnable(GL_TEXTURE_2D);

        //glTranslatef(0,0,0);
        gluDisk(quadratic,0.0,.1,32,32);
        glDisable(GL_TEXTURE_2D);

        glPopMatrix();

        glPushMatrix();
        reflect(.7,.2,.2,60);
        glTranslatef(0,-.05,0);
        glScalef(0.01,.025,.1);
        drawBox();
        glTranslated(7,0,0);
        drawBox();
        glTranslated(-4,3,0);
        drawBox();
        glPopMatrix();

        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

}

void office()
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[4]);
    glEnable(GL_TEXTURE_2D);
    reflect(1,1,1,60);
    drawBox();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,2,0);
    glScaled(1.1,.2,1.1);
    reflect(.5,.5,.5,60);
    glBindTexture(GL_TEXTURE_2D,ID[1]);
    drawBox();
    glDisable(GL_TEXTURE_2D);
    glScaled(.1,10,.1);
    glTranslatef(-15,0,15);
    reflect(1,1,1,60);
    //reflect(1,0,0,60);
    glBindTexture(GL_TEXTURE_2D,ID[2]);
    glEnable(GL_TEXTURE_2D);
    drawBox();
    glDisable(GL_TEXTURE_2D);

    glTranslated(0,1.75,0);
    glScaled(1.5,0.03,1.5);
    glBindTexture(GL_TEXTURE_2D,ID[1]);
    glEnable(GL_TEXTURE_2D);
    drawBox();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glTranslated(-2,2.4,2);
    glRotated(-90,1,0,0);
    glScalef(.66,1,.2);
    reflect(1,1,1,60);
    glBindTexture(GL_TEXTURE_2D,ID[1]);
    glEnable(GL_TEXTURE_2D);
    //reflect(1,1,1,60);
    drawtri();
    glTranslatef(1,0,0);
    drawtri();
    glTranslatef(1,0,0);
    drawtri();
    glTranslatef(1,0,0);
    drawtri();
    glTranslatef(1,0,0);
    drawtri();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void trans()
{

    glPushMatrix();
    glTranslatef(1,2,0);
    glScalef(1,1,0.9);
    glTranslatef(0,0,0.2);
    glBindTexture(GL_TEXTURE_2D,ID[8]);
    glEnable(GL_TEXTURE_2D);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,ID[7]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.1,2,.1);
    drawBox();
    glTranslated(20,0,0);
    drawBox();
    glTranslated(0,0,20);
    drawBox();
    glTranslated(-20,0,0);
    drawBox();
    glPopMatrix();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}

void dome()
{
    glPushMatrix();

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluQuadricOrientation(quadratic, GLU_OUTSIDE);
    gluQuadricNormals(quadratic, true);
    gluQuadricTexture(quadratic, true);

    gluSphere(quadratic,1.1,32,32);

    gluCylinder(quadratic,1,1,3.0f,32,32);

    glPopMatrix();
}

void road()
{
    glPushMatrix();
    glScalef(4.5,.1,.15);
    reflect(0,0,0,60);
    drawBox();
    glTranslatef(-1.7,.1,0.75);
    glScalef(.1,1,.2);
    reflect(1,1,0,60);
    drawBox();
    glTranslatef(8,0,0.1);
    drawBox();
    glTranslatef(8,0,0);
    drawBox();
    glTranslatef(8,0,0);
    drawBox();
    glTranslatef(8,0,0);
    drawBox();


    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5,5,-5,5, 4,50);
    //gluPerspective(60,1,5,100);
    //glOrtho(-5,5,-5,5, 4, 50);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eye[0],eye[1],eye[2],look[0],look[1],look[2],up[0],up[1],up[2]);

    glViewport(0, 0, windowHeight, windowWidth);

    glBindTexture(GL_TEXTURE_2D,ID[3]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0,0,Tzval);
    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );

    glPushMatrix();
    glScalef(5,0.2,5);
    reflect(1,1,1,60);
    drawBox();
    //glPopMatrix();
    //glPushMatrix();
    glDisable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D,ID[1]);
    glEnable(GL_TEXTURE_2D);

    glTranslatef(0,2,.125);
    glScalef(0.9,0.5,0.9);
    reflect(0.3,0.3,0.3,60);

    drawBox();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.6,0);
    glPushMatrix();
    glTranslatef(0,-.18,6);
    road();
    glTranslatef(.9,0,-.9);
    glRotatef(90,0,1,0);

    glScalef(.5,1,1.5);
    road();
    glPopMatrix();

    glPushMatrix();
    reflect(1,1,1,60);
    glBindTexture(GL_TEXTURE_2D,ID[4]);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(4,1,9);
    glScalef(0.45,0.4,0.5);
    glRotated(90,1,0,0);
    dome();
    glTranslatef(4,0,0);
    dome();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    reflect(1,1,1,60);
    glTranslatef(2,0,3);
    glScalef(0.7,0.7,0.7);
    //drawBox();
    dustbin();
    glTranslatef(3.5,0,0);
    dustbin();
    glTranslatef(0,0,-3.5);
    dustbin();
    glTranslatef(-3.5,0,0);
    dustbin();
    glScaled(.8,.8,.8);
    glTranslatef(-5,0,5);
    office();
    glTranslatef(-6,0,0);
    office();
    glTranslatef(-6,0,0);
    office();
    glTranslatef(0,0,6);
    glScalef(0.5,0.5,0.5);
    trans();
    glTranslatef(2,0,6.5);
    glScalef(0.31,0.31,0.31);
    trans();



    /*
    glTranslatef(-3.5,0,0);
    glScalef(1,1,0.5);
    glRotatef(-90,1,0,0);
    glScalef(1,1,0.5);
    drawtri();
    */

    glPopMatrix();


    glPopMatrix();


    glPopMatrix();

/*
    LoadTexture("/home/samin/Desktop/study/4.2/CSE4208/Texture/Texture/grass.bmp");
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0,0,Tzval);
    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );
    glTranslatef(0,-.5,-3);
    glScalef(3,0.2,3);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
*/

    glFlush();
    glutSwapBuffers();

}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'i':
        moveForward(look,eye);
        break;
    case 'k':
        moveBackward(look,eye);
        break;

    case 'a':
        Yaw(eye,look,up,bita);
        break;
    case 'd':
        Yaw(eye,look,up,bita,false);
        break;
    case 'w':
        Pitch(eye,look,up,theta);
        break;
    case 's':
        Pitch(eye,look,up,theta,false);
        break;
    case 'q':
        Roll(eye,look,up,alpha);
        break;
    case 'e':
        Roll(eye,look,up,alpha,false);
        break;
    case 'b':
        birds = !birds;
        if(birds){
            eye[0] = 0;
            eye[1] = 20;
            eye[2] = 2;
            look[0] = 0;
            look[1] = 0;
            look[2] = 0;
            up[0] = 0;
            up[1] = 0;
            up[2] = -1;
        }
        else{
            eye[0] = 0;
            eye[1] = 2;
            eye[2] = 20;
            look[0] = 0;
            look[1] = 0;
            look[2] = 0;
            up[0] = 0;
            up[1] = 1;
            up[2] = 0;
        }
        break;

    case 'S':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case '+':
        Tzval+=0.2;
        break;

    case '-':
        Tzval-=0.2;
        break;

    case 27:	// Escape key
        exit(1);
    }
}


void animate()
{
    if (bRotate == true)
    {
        theta += 0.8;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.8;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    glutPostRedisplay();

}

void LoadTexture(const char*filename,int a)
{
    glGenTextures(1, &ID[a]);
    glBindTexture(GL_TEXTURE_2D, ID[a]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[a]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Texture-Demo");
    LoadTexture("/home/samin/Desktop/study/4.2/CSE4208/Project-Final/Nuclear_powerplant/img/base.bmp",1);
    LoadTexture("/home/samin/Desktop/study/4.2/CSE4208/Project-Final/Nuclear_powerplant/img/brick.bmp",2);
    LoadTexture("/home/samin/Desktop/study/4.2/CSE4208/Project-Final/Nuclear_powerplant/img/grass.bmp",3);
    LoadTexture("/home/samin/Desktop/study/4.2/CSE4208/Project-Final/Nuclear_powerplant/img/office.bmp",4);
    LoadTexture("/home/samin/Desktop/study/4.2/CSE4208/Project-Final/Nuclear_powerplant/img/window.bmp",5);
    LoadTexture("/home/samin/Desktop/study/4.2/CSE4208/Project-Final/Nuclear_powerplant/img/net.bmp",6);
    LoadTexture("/home/samin/Desktop/study/4.2/CSE4208/Project-Final/Nuclear_powerplant/img/transformer.bmp",8);

    LoadTexture("/home/samin/Desktop/study/4.2/CSE4208/Project-Final/Nuclear_powerplant/img/kettle.bmp",7);




    //LoadTexture("C:\\Users\\NLP Lab\\Desktop\\1707006\\Lab_3\\Texture\\brick.bmp");

    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);

    //glClearColor(0,0,0,1);


    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    light();


    glutMainLoop();

    return 0;
}

