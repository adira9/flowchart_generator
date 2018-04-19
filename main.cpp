#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

#define SIN(x) sin(x * 3.141592653589/180)
#define COS(x) cos(x * 3.141592653589/180)

int n;
int iterations = 0;
int refreshtime = 100; //milliseconds
//float points_list1[4][2] = {{100, 100}, {150, 200}, {200, 200}, {200, 150}};
float points_list1[4][2] = {{-50, 0}, {0, 100}, {50, 0}, {0, -100}};
float ans_list[10][2];
float x_pivot, y_pivot;
int angle;

void plot(int x,int y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void myinit(){
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);
    glPointSize(3.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250.0,250.0,-250.0,250.0);
}

void timer(int argument)
{
   glutPostRedisplay();
   if (iterations <= 160) {
      glutTimerFunc(refreshtime, timer, iterations);
      iterations += angle;
   }
}

void rotate(){
    int i = 0;
    /*glBegin(GL_LINE_LOOP);
    for(i=0;i<n;i++){
        glColor3f(0,0,1);
        glVertex2f(points_list1[i][0], points_list1[i][1]);
    }
    glEnd();*/
    i=0;
    while (i < n)
    {
        int x_shifted = points_list1[i][0] - x_pivot;
        int y_shifted = points_list1[i][1] - y_pivot;
        points_list1[i][0] = x_pivot + (x_shifted*COS(angle)
                          - y_shifted*SIN(angle));
        points_list1[i][1] = y_pivot + (x_shifted*SIN(angle)
                          + y_shifted*COS(angle));
        //printf("(%f, %f) ", points_list1[i][0], points_list1[i][1]);
        ans_list[i][0] = points_list1[i][0];
        ans_list[i][1] = points_list1[i][1];
        //plot(points_list1[i][0], points_list1[i][1]);
        i++;
    }
    glBegin(GL_LINE_LOOP);
    for(i=0;i<n;i++){
        glColor3f(0,1,0);
        glVertex2f(ans_list[i][0], ans_list[i][1]);
    }
    glEnd();
}

void reshape(GLsizei width, GLsizei height){
    glViewport(0.0, 0.0, width, height);
}

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glPointSize(3.0f);
    rotate();
    glPopMatrix();
    glFlush();
}

int main(int argc,char **argv){
    /*printf("enter the number of vertices of the polygon\n");
    cin>>n;
    printf("enter the vertices of the polygon (x,y)\n");
    for(int i=0; i<n; i++)
        cin>>points_list1[i][0]>>points_list1[i][1];
    printf("enter the pivot point about which the polygon is supposed to be rotated\n");
    cin>>x_pivot>>y_pivot;
    printf("enter the angle of rotation in degrees\n");
    cin>>angle;*/
    n = 4;
    x_pivot = 0;
    y_pivot = 0;
    angle = 10;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500,500);
    glutCreateWindow("rotation of polygon from the scratch");
    glutReshapeFunc(reshape);
    myinit();
    glutTimerFunc(0, timer, iterations);
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    return 0;
}
