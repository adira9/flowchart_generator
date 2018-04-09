//Parallelogram drawing Fn.
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<windows.h>
#include<math.h>
#include<string>

using namespace std;

float X, Y; //Center coordinates.

int width=1000;
int height=1000;
char *text="AutoResizeBitch";


float RoundValue(float v)
{
  return floor(v + 0.5);
}

void LineDDL(double X0,double Y0, double X1, double Y1) // P0-P1 line.
{
  double dx=(X1-X0);
  double dy=(Y1-Y0);
  double steps;
  float xInc,yInc,x=X0,y=Y0;
  /* Find out whether to increment x or y */
  steps=(fabs(dx)>fabs(dy))?(fabs(dx)):(fabs(dy));
  xInc=dx/(float)steps;
  yInc=dy/(float)steps;
    glPointSize(0.5);
  glBegin(GL_POINTS);
  glVertex2d(x,y);
  int k;
  /* For every step, find an intermediate vertex */
  for(k=0;k<steps;k++)
  {
    x+=xInc;
    y+=yInc;
    glVertex2d(RoundValue(x),RoundValue(y));
  }
  glEnd();
  glFlush();
}

void DrawPara(double Side_length, int height) //count = length of the string. space = space b/w the shape and the string.
{
    Side_length=Side_length;
    float space=height*0.7;
    glColor3f(1.0,1.0,1.0);
    LineDDL(X-(Side_length/2),Y+height/2,X+(Side_length/2)+space+10,Y+height/2); //A-B
    LineDDL(X+(Side_length/2)+space+10,Y+height/2,X+Side_length/2+10,Y-height/2 );//B-C
    LineDDL(X-(Side_length/2)-space,Y-height/2,X+(Side_length/2)+10,Y-height/2);//C-D
    LineDDL(X-(Side_length/2)-space,Y-height/2,X-Side_length/2,Y+height/2);//D-A

}

void Init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GLUT_SINGLE|GLUT_RGB);
    glLoadIdentity();
    glOrtho(-500.0,500.0,-500.0,500.0,0.0,1.0);
}

void RenderBitmap(float x,float y, void *font, char *string)
{
    char *c;
    glRasterPos2f(x,y);
    for(c=string;*c!='\0';c++)
    {
        glutBitmapCharacter(font,*c);
    }

}

void PgramBubble(char *text)
{
  glColor3f(1.f,1.f,1.f);
    char buf[100]={0};
    const unsigned char *ptr=(unsigned char*)&buf[0];
    sprintf(buf,text);
    //printf("%d\n",glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr));
    int text_length=glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr);
    //printf("%d\n",glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24,buf[0]));
    DrawPara(text_length*2.5,50);
    RenderBitmap(X-text_length,Y-50/4,GLUT_BITMAP_TIMES_ROMAN_24,buf);
}

void IntroScreen()
{
  PgramBubble(text);
}

void Display()
{
    IntroScreen();
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
    X=0.0;
    Y=0.0;

    Init();

    glutDisplayFunc(Display);

    glutMainLoop();
    return 0;
}
