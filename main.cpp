#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<windows.h>

using namespace std;

int width=480;
int height=640;

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GLUT_SINGLE|GLUT_RGB);
    glLoadIdentity();
    glOrtho(-90.0,100.0,-15.0,100.0,0.0,1.0);
}

void renderbitmap(float x,float y, void *font, char *string)
{
    char *c;
    glRasterPos2f(x,y);
    for(c=string;*c!='\0';c++)
    {
        glutBitmapCharacter(font,*c);
    }

}

void introscreen()
{
    glColor3f(1.f,1.f,1.f);
    char buf[100]={0};
    const unsigned char *ptr=(unsigned char*)&buf[0];
    sprintf(buf,"AI");
    printf("%d\n",glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24,ptr));
    //printf("%d\n",glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24,buf[0]));
    glBegin(GL_LINE_LOOP);
    glVertex2f(-40,60);
    glVertex2f(40,60);
    glVertex2f(40,40);
    glVertex2f(-40,40);
    glEnd();
    renderbitmap(-5,50,GLUT_BITMAP_TIMES_ROMAN_24,buf);

}

void display()
{
    introscreen();
    glFlush();
    glutPostRedisplay();
}


int main(int arg, char **argv)
{
    glutInit(&arg,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(30,30);
    glutCreateWindow("Text trial");

    init();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

