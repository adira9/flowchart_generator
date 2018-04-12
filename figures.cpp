#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdio.h>
#include <stdlib.h>
#define ROUND(x) ((int)(x+0.5))

int a,b,d,x,y;
void init(void)
{
 glClearColor(1.0,1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0.0,400.0,0.0,400.0);
}
void setPixel(GLint x,GLint y)
{
 //glColor3f(255,255,255);
 glBegin(GL_POINTS);
 glVertex2f(x,y);
 glEnd();
}
void Linemp(int x0,int y0,int xn,int yn)
{
 int x,y,dx,dy,pk;

 glColor3f(1,0,0);
 setPixel(x0,y0);
 dx=xn-x0;
 dy=yn-y0;
 pk=2*dy-dx;
 x=x0;
 y=y0;
while(x<xn)
 {
  if(pk<0)
  {
   pk=pk+2*dy;
  }
  else
  {
   pk=pk+2*dy-2*dx;
   ++y;
  }
  ++x;
  setPixel(x,y);
 }

}
void Linedda(int x0,int y0,int xn,int yn){
 int dx=xn-x0,dy=yn-y0,steps,k;
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


void drawRectangle(int a,int b){
glClear(GL_COLOR_BUFFER_BIT);
Linemp(x-ROUND(a/2),y+ROUND(b/2),x+ROUND(a/2),y+ROUND(b/2));
Linedda(x+ROUND(a/2),y+ROUND(b/2),x+ROUND(a/2),y-ROUND(b/2));
Linemp(x-ROUND(a/2),y-ROUND(b/2),x+ROUND(a/2),y-ROUND(b/2));
Linedda(x-ROUND(a/2),y-ROUND(b/2),x-ROUND(a/2),y+ROUND(b/2));
glFlush();
}
void Rectangle(){
drawRectangle(a,b);
}
void drawDaimond(int d){
glClear(GL_COLOR_BUFFER_BIT);
Linemp(x-ROUND(d/2),y,x,y+ROUND(d/2));
Linedda(x,y+ROUND(d/2),x+ROUND(d/2),y);
Linemp(x,y-ROUND(d/2),x+ROUND(d/2),y);
Linedda(x,y-ROUND(d/2),x-ROUND(d/2),y);
glFlush();
}
void daimond(){
drawDaimond(d);
}
int main (int argc,char **argv)
{ x=0;
y=0;
a=50;
b=50;
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(50,25);
glutInitWindowSize(500,500);
glutCreateWindow("Rectangle");
init();
//glutDisplayFunc(daimond);
glutDisplayFunc(Rectangle);
glutMainLoop();
 return 0;
}
