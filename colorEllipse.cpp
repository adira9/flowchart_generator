#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#define ROUND(x)((int)(x+0.5))

float xc,yc,rx,ry;
void scanline(int,int);
void ellipseMidpoint(float,float);
void colorEllipse(float,float);

void setPixel(GLfloat x,GLfloat y)
{
 //glColor3f(255,255,255);
 glBegin(GL_POINTS);
 glVertex2f(x,y);
 glEnd();
}
 void displayEllipse(void)
 {
 glClear (GL_COLOR_BUFFER_BIT);
 glColor3f (1.0, 0.0, 0.0);
 glBegin(GL_POINTS);
 ellipseMidpoint(rx,ry);
colorEllipse(rx,ry);

 glEnd();
 glFlush();
 }


void drawEllipse(float x, float y)
{
    int p1[] = {(int)xc+x, (int)yc+y};
    int p2[] = {(int)xc-x, (int)yc+y};
    int p3[] = {(int)xc+x, (int)yc-y};
    int p4[] = {(int)xc-x, (int)yc-y};
    glColor3f (1.0, 1.0, 1.0);
    glVertex2iv(p1);
    glVertex2iv(p2);
    glVertex2iv(p3);
    glVertex2iv(p4);
}

void ellipseMidpoint(float rx, float ry)
{
    float rxSq = rx * rx;
    float rySq = ry * ry;
    float x = 0, y = ry, p;
    float px = 0, py = 2 * rxSq * y;
    drawEllipse(x, y);

    p = rySq - (rxSq * ry) + (0.25 * rxSq);
    while (px < py)
    {
        x++;
        px = px + 2 * rySq;
        if (p < 0)
            p = p + rySq + px;
        else
        {
            y--;
            py = py - 2 * rxSq;
            p = p + rySq + px - py;
        }
        drawEllipse(x, y);
    }

    p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;
    while (y > 0)
    {
        y--;
        py = py - 2 * rxSq;
        if (p > 0)
            p = p + rxSq - py;
        else
        {
            x++;
            px = px + 2 * rySq;
            p = p + rxSq - py + px;
        }
        drawEllipse(x, y);
    }
}
void Linedda(float x0,float y0,float xn,float yn){
 float dx=xn-x0,dy=yn-y0,steps,k;
 float xIncrement,yIncrement,x=x0,y=y0;
 glColor3f (1.0, 0.0, 0.0);
 if(abs(dx)>abs(dy))
 steps=abs(dx);
 else steps=abs(dy);
 xIncrement=dx/(float)steps;
 yIncrement=dy/(float)steps;
 setPixel(ROUND(x),ROUND(y));
for(k=0;k<steps;k++)
 {
 x+=xIncrement;
 y+=yIncrement;
 setPixel(ROUND(x),ROUND(y));
 }
 }

void colorEllipse(float rx,float ry){
float i;
float yco,xco;
for(i=-rx;i<=rx;i++){
    yco=(ry*(sqrt(pow(rx,2)-pow(i,2))))/rx;
    Linedda(i,-yco,i,+yco);
    Linedda(-i,-yco,-i,+yco);
}
}

 void init(void)
 {
 glClearColor (0.0, 0.0, 0.0, 0.0);
 glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
 }
int main(int argc, char** argv)
{
rx=50;
ry=25;
 glutInit(&argc, argv);
 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize (700, 500);
 glutInitWindowPosition (100, 100);
 xc=0;
 yc=0;
 glutCreateWindow ("Ellipse : Scanline Filling Method ");
 init ();
 glutDisplayFunc(displayEllipse);
 glutMainLoop();
 return 0;
}
